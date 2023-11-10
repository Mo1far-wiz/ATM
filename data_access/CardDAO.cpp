//
// Created by Oleksandr on 05.11.2023.
//

#include <QDate>
#include "CardDAO.h"

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
                          "(id SERIAL PRIMARY KEY, "
                          "cardNumber VARCHAR(16) NOT NULL, "
                          "cvv VARCHAR(3) NOT NULL, "
                          "owner INT NOT NULL, "  // Use INT as data type for the owner
                          "currentBalance INTEGER NOT NULL, "
                          "expireDate DATE NOT NULL, "
                          "cardType_id INT, "
                          "transactionCommission INT NOT NULL, "
                          "withdrawCommission INT NOT NULL, "
                          "pin TEXT NOT NULL, "     // Add a comma here
                          "FOREIGN KEY(cardType_id) REFERENCES CardType(id), "
                          "FOREIGN KEY(owner) REFERENCES User(id));");



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
            // Retrieve user data from the query result and create a User object
            uint32_t id                     = selectQuery.value("id").toUInt();
            QString cardNumber              = selectQuery.value("cardNumber").toString();
            QString cvv                     = selectQuery.value("cvv").toString();
            uint32_t owner                  = selectQuery.value("owner").toUInt();
            uint32_t currentBalance         = selectQuery.value("currentBalance").toUInt();
            QDate expireDate                = selectQuery.value("expireDate").toDate();
            uint32_t cardType_id            = selectQuery.value("cardType_id").toUInt();
            uint32_t transactionCommission  = selectQuery.value("transactionCommission").toUInt();
            uint32_t withdrawCommission     = selectQuery.value("withdrawCommission").toUInt();
            QString pin                     = selectQuery.value("pin").toString();

            Card* card = new Card(id, cardNumber.toStdString(), currentBalance, cvv, expireDate, CardType(cardType_id));
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
