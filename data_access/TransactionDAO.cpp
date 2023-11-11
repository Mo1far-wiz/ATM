//
// Created by Oleksandr on 05.11.2023.
//
#include "TransactionDAO.h"

#include <QDate>
#include <QDebug>
#include <QtSql>
#include <QtTest/qtestcase.h>

TransactionDAO &TransactionDAO::getInstance() {
    static TransactionDAO instance;
    initialize();
    return instance;
}

void TransactionDAO::initialize() {
    static bool isInitialized = false;
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    } else if (isInitialized) {
        qInfo() << "Database is already initialized.";
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'Transaction' "
                          "(id          SERIAL      PRIMARY KEY, "
                          "fromCardId   SERIAL      NOT NULL, "
                          "toCardId     SERIAL      NOT NULL, "
                          "amount       DOUBLE      NOT NULL, "
                          "FOREIGN KEY(fromCardId) REFERENCES Card(id), "
                          "FOREIGN KEY(toCardId) REFERENCES Card(id));");


    qInfo() << "Creation of the 'Transaction' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

Transaction *TransactionDAO::deserializeTransaction(const QSqlQuery &executedQuery) const {
    uint32_t id         = executedQuery.value("id").toUInt();
    uint32_t fromCardId = executedQuery.value("fromCardId").toUInt();
    uint32_t toCardId   = executedQuery.value("toCardId").toUInt();
    double amount       = executedQuery.value("amount").toUInt();

    Transaction * transaction = nullptr;

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

QList<Transaction *> TransactionDAO::getCardTransactions(uint32_t cardId) const{
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return {};
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Transaction "
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

QList<Transaction *> TransactionDAO::getUserTransactions(uint32_t userId) const{
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return {};
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT DISTINCT * FROM Transaction "
                        "WHERE fromCardId IN ("
                        "SELECT id FROM Card WHERE owner = :from)"
                        "OR"
                        "toCardId IN ("
                        "SELECT id FROM Card WHERE owner = :to");
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
