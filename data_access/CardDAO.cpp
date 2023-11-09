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

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'Card' "
                          "(id SERIAL PRIMARY KEY, "
                          "cardNumber VARCHAR(16) NOT NULL, "
                          "cvv VARCHAR(3) NOT NULL, "
                          "owner SERIAL NOT NULL,"
                          "currentBalance INTEGER NOT NULL, "
                          "expireDate DATE NOT NULL, "
                          "cardType_id INT, "
                          "transactionCommission INT NOT NULL, "
                          "withdrawCommission INT NOT NULL, "
                          "pin TEXT NOT NULL"
                          "FOREIGN KEY(cardType_id) REFERENCES CardType(id), "
                          "FOREIGN KEY(owner) REFERENCES User(id));");


    qDebug() << "creation of the 'Card' table was successful: " << createQuery.isActive();
    isInitialized = true;
}
