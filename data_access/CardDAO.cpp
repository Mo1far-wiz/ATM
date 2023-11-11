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
    if (isInitialized || !QSqlDatabase::database().isOpen()) {
        return;
    }
    QSqlQuery createQueryCardType("CREATE TABLE IF NOT EXISTS 'CardType' "
                                  "(id SERIAL PRIMARY KEY, "
                                  "typeName TEXT NOT NULL)");

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'Card' "
                          "(id              SERIAL PRIMARY KEY, "
                          "cardNumber       CHAR(16)    NOT NULL, "
                          "cvv              CHAR(3)     NOT NULL, "
                          "owner            SERIAL      NOT NULL, "
                          "currentBalance   DOUBLE      NOT NULL, "
                          "expireDate       DATE        NOT NULL, "
                          "cardType_id              INTEGER         NOT NULL, "
                          "transactionCommission    FLOAT(1, 3)     NOT NULL, "
                          "withdrawCommission       FLOAT(1, 3)     NOT NULL, "
                          "creditLimit              INTEGER         NULL, "
                          "pin                      TEXT            NOT NULL, "
                          "FOREIGN KEY(cardType_id) REFERENCES CardType(id), "
                          "FOREIGN KEY(owner)       REFERENCES User(id));");



    qInfo() << "creation of the 'CardType' table was successful: " << createQueryCardType.isActive();
    qInfo() << "creation of the 'Card' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

Card *CardDAO::getById(const QString &id) const {
    return nullptr;
}

Card *CardDAO::deserializeCard(QSqlQuery &selectQuery) const {
    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            // Retrieve user data from the query result and create a Card object
            uint32_t id                     = selectQuery.value("id").toUInt();
            QString cardNumber              = selectQuery.value("cardNumber").toString();
            QString cvv                     = selectQuery.value("cvv").toString();
            uint32_t owner                  = selectQuery.value("owner").toUInt();
            double currentBalance           = selectQuery.value("currentBalance").toDouble();
            QDate expireDate                = selectQuery.value("expireDate").toDate();
            uint32_t cardType_id            = selectQuery.value("cardType_id").toUInt();
            float transactionCommission     = selectQuery.value("transactionCommission").toFloat();
            float withdrawCommission        = selectQuery.value("withdrawCommission").toFloat();
            uint creditLimit                = selectQuery.value("creditLimit").isNull() ?
                                                    0 : selectQuery.value("creditLimit").toUInt();
            QString pin                     = selectQuery.value("pin").toString();

            Card* card = nullptr;
            if(static_cast<CardType>(cardType_id) == CardType::Credit)
            {
                //card = new CreditCard(id, cardNumber.toStdString(), currentBalance, cvv.toStdString(), expireDate.day(), CardType::Credit);
            }
            else if(static_cast<CardType>(cardType_id) == CardType::Debit)
            {
                //card = new DebitCard(id, cardNumber.toStdString(), currentBalance, cvv.toStdString(), expireDate.day(), CardType::Debit);
            }
            qInfo() << "User with ID" << id << "was found.";
            return card;
        } else {
            qWarning() << "User with " << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString() << "not found.";
        }
    } else {
        qCritical() << "Error retrieving user:" << selectQuery.lastError().text()
                    <<"\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}

Card *CardDAO::getByCardNum(const QString &id) const {
    return nullptr;
}
