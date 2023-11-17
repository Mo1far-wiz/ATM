//
// Created by Oleksandr on 05.11.2023.
//
#include "TransactionDAO.h"

#include <QDate>
#include <QDebug>
#include <QtSql>
#include <QtTest/qtestcase.h>

uint32_t TransactionDAO::_id = 1;

TransactionDAO &TransactionDAO::getInstance() {
    static TransactionDAO instance;
    static bool isInitialized = false;
    if(!isInitialized)
    {
        initialize();
    }
    isInitialized = true;
    return instance;
}

void TransactionDAO::initialize() {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'Transaction' "
                          "(id          SERIAL      PRIMARY KEY, "
                          "fromCardId   SERIAL      NOT NULL, "
                          "toCardId     SERIAL      NOT NULL, "
                          "amount       DOUBLE      NOT NULL, "
                          "FOREIGN KEY(fromCardId) REFERENCES Card(fromCardId), "
                          "FOREIGN KEY(toCardId) REFERENCES Card(toCardId));");


    qInfo() << "Creation of the 'Transaction' table was successful: \t" << createQuery.isActive();
}

Transaction *TransactionDAO::deserializeTransaction(const QSqlQuery &executedQuery) const {
    uint32_t id         = executedQuery.value("id").toUInt();
    uint32_t fromCardId = executedQuery.value("fromCardId").toUInt();
    uint32_t toCardId   = executedQuery.value("toCardId").toUInt();
    double amount       = executedQuery.value("amount").toUInt();

    Transaction * transaction = new Transaction(id, fromCardId, toCardId, amount);

    qInfo() << "Transaction with ID" << id << "was found.";
    return transaction;
}

QList<Transaction *> TransactionDAO::multipleCardsDeserialization(QSqlQuery &executedQuery) const {
    QList<Transaction *> transactions;
    while (executedQuery.next()) {
        Transaction *transaction = deserializeTransaction(executedQuery);
        if (transaction) {
            transactions.append(transaction);
        } else {
            qWarning() << "Transactions with " << executedQuery.boundValueName(0) << executedQuery.boundValue(0).toString()
                       << "not found.";
            break;
        }
    }

    return transactions;
}

QList<Transaction *> TransactionDAO::getCardTransactions(const uint32_t &cardId) const{
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return {};
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM 'Transaction' "
                        "WHERE fromCardId = :fromCardId OR toCardId = :toCardId");
    selectQuery.bindValue(":fromCardId", cardId);
    selectQuery.bindValue(":toCardId", cardId);

    if (selectQuery.exec()) {
        return multipleCardsDeserialization(selectQuery);
    } else {
        qCritical() << "Error retrieving transactions:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return {};
}

QList<Transaction *> TransactionDAO::getUserTransactions(const uint32_t &userId) const{
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return {};
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT DISTINCT * FROM 'Transaction' "
                        "WHERE fromCardId IN ("
                        "SELECT id FROM Card WHERE owner = :from)"
                        "OR"
                        "toCardId IN ("
                        "SELECT id FROM Card WHERE owner = :to);");
    selectQuery.bindValue(":from", userId);
    selectQuery.bindValue(":to", userId);

    if (selectQuery.exec()) {
        return multipleCardsDeserialization(selectQuery);
    } else {
        qCritical() << "Error retrieving transactions:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return {};
}

void TransactionDAO::addTransaction(const Transaction* transaction) const{
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    }
    else if (!transaction)
    {
        qCritical() << "Can't add transaction, transaction is null.";
        return;
    }

    // Prepare the SQL query
    QSqlQuery insertTransactionQuery;
    insertTransactionQuery.prepare("INSERT INTO 'Transaction' (id, fromCardId, toCardId, amount) VALUES (:id, :fromCardId, :toCardId, :amount)");

    insertTransactionQuery.bindValue(":id", _id++);
    insertTransactionQuery.bindValue(":fromCardId", transaction->GetFrom());
    insertTransactionQuery.bindValue(":toCardId", transaction->GetTo());
    insertTransactionQuery.bindValue(":amount", transaction->GetAmount());

    // Execute the query
    if (insertTransactionQuery.exec()) {
        qInfo() << "Transaction with ID " << _id-1 << ", fromCardID " << transaction->GetFrom() << ", toCardID " << transaction->GetTo() << " added successfully.";
    } else {
        qCritical() << "Error adding transaction:" << insertTransactionQuery.lastError().text()
                    << "\n\t For query : " << insertTransactionQuery.lastQuery();
    }
}
