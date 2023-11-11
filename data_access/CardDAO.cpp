//
// Created by Oleksandr on 05.11.2023.
//

#include "CardDAO.h"

#include <QDate>
#include <QDebug>
#include <QtSql>
#include <QtTest/qtestcase.h>

#include "Cards/CreditCard.h"
#include "Cards/DebitCard.h"

CardDAO &CardDAO::getInstance() {
    static CardDAO instance;
    initialize();
    return instance;
}

void CardDAO::initialize() {
    static bool isInitialized = false;
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    } else if (isInitialized) {
        qInfo() << "Database is already initialized.";
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'Card' "
                          "(id                      SERIAL          PRIMARY KEY, "
                          "cardNumber               CHAR(16)        NOT NULL, "
                          "cvv                      CHAR(3)         NOT NULL, "
                          "owner                    SERIAL          NOT NULL, "
                          "currentBalance           DOUBLE          NOT NULL, "
                          "expireDate               DATE            NOT NULL, "
                          "cardType_id              INTEGER         NOT NULL, "
                          "transactionCommission    FLOAT(1, 3)     NOT NULL, "
                          "withdrawCommission       FLOAT(1, 3)     NOT NULL, "
                          "creditLimit              INTEGER         NULL, "
                          "pin                      TEXT            NOT NULL, "
                          "FOREIGN KEY(cardType_id) REFERENCES CardType(id), "
                          "FOREIGN KEY(owner)       REFERENCES User(id));");

    qInfo() << "Creation of the 'Card' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

Card *CardDAO::getById(uint32_t id) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Card WHERE id = :id");
    selectQuery.bindValue(":id", id);

    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            return deserializeCard(selectQuery);
        } else {
            qWarning() << "Card with " << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString()
                       << "not found.";
        }
    } else {
        qCritical() << "Error retrieving card:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}

Card *CardDAO::deserializeCard(QSqlQuery &executedQuery) const {
    // Retrieve user data from the query result and create a Card object
    uint32_t id                     = executedQuery.value("id").toUInt();
    QString cardNumber              = executedQuery.value("cardNumber").toString();
    QString cvv                     = executedQuery.value("cvv").toString();
    uint32_t owner                  = executedQuery.value("owner").toUInt();
    double currentBalance           = executedQuery.value("currentBalance").toDouble();
    QDate expireDate                = executedQuery.value("expireDate").toDate();
    uint32_t cardType_id            = executedQuery.value("cardType_id").toUInt();
    float transactionCommission     = executedQuery.value("transactionCommission").toFloat();
    float withdrawCommission        = executedQuery.value("withdrawCommission").toFloat();
    uint creditLimit                = executedQuery.value("creditLimit").isNull() ?
                                                    0 : executedQuery.value("creditLimit").toUInt();
    QString pin                     = executedQuery.value("pin").toString();

    Card *card = nullptr;
    if (static_cast<CardType>(cardType_id) == CardType::Credit) {
        //card = new CreditCard(id, cardNumber.toStdString(), currentBalance, cvv.toStdString(), expireDate.day(), CardType::Credit);
    } else if (static_cast<CardType>(cardType_id) == CardType::Debit) {
        //card = new DebitCard(id, cardNumber.toStdString(), currentBalance, cvv.toStdString(), expireDate.day(), CardType::Debit);
    }
    qInfo() << "Card with ID" << id << "was found.";
    return card;
}

Card *CardDAO::getByCardNum(const QString &cardNum) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Card WHERE cardNumber = :cardNumber");
    selectQuery.bindValue(":cardNumber", cardNum);

    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            return deserializeCard(selectQuery);
        } else {
            qWarning() << "Card with " << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString()
                       << "not found.";
        }
    } else {
        qCritical() << "Error retrieving card:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}

Card *CardDAO::getByUserId(uint32_t id) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Card WHERE owner = :owner");
    selectQuery.bindValue(":owner", id);

    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            return deserializeCard(selectQuery);
        } else {
            qWarning() << "Card with "
                       << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString()
                       << "not found.";
        }
    } else {
        qCritical() << "Error retrieving card:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}

QList<Card *> CardDAO::multipleCardsDeserialization(QSqlQuery &executedQuery) const {
    QList<Card *> cards;

    while (executedQuery.next()) {
        Card *card = deserializeCard(executedQuery);
        if (card) {
            cards.append(card);
        } else {
            qWarning() << "Cards with " << executedQuery.boundValueName(0) << executedQuery.boundValue(0).toString()
                       << "not found.";
            break;
        }
    }

    return cards;
}

QList<Card *> CardDAO::getAllUserCards(uint32_t id) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return {};
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Card WHERE owner = :owner");
    selectQuery.bindValue(":owner", id);

    if (selectQuery.exec()) {
        return multipleCardsDeserialization(selectQuery);
    } else {
        qCritical() << "Error retrieving cards:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return {};
}