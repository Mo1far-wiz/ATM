//
// Created by Oleksandr on 05.11.2023.
//

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



    qDebug() << "creation of the 'CardType' table was successful: " << createQueryCardType.isActive();
    qDebug() << "creation of the 'Card' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

Card *CardDAO::getById(const QString &id) const {
    return nullptr;
}

Card *CardDAO::deserializeCard(const QSqlQuery &query) const {
//    Card* card = new Card(query.value(0).toUInt(), CardType(query.value(1).toInt()),
//                          query.value(2).toString(), );
//    if (query.value(4).toBool()) card->block();
//    return card;
    return nullptr;
}
