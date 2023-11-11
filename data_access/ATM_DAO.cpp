//
// Created by Oleksandr on 05.11.2023.
//

#include "ATM_DAO.h"

#include <QSqlDatabase>

ATM_DAO &ATM_DAO::getInstance() {
    static ATM_DAO instance;
    initialize();
    return instance;
}

void ATM_DAO::initialize() {
    static bool isInitialized = false;
    if (isInitialized || !QSqlDatabase::database().isOpen()) {
        return;
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'ATM' "
                          "(id SERIAL PRIMARY KEY, "
                          "bankId SERIAL NOT NULL, "
                          "currentBalance INTEGER NOT NULL, "
                          "moneyLeft INT NOT NULL, "
                          "currentCardId SERIAL NOT NULL);");

    qInfo() << "creation of the 'ATM' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

ATM *ATM_DAO::deserializeATM(const QSqlQuery &query) const {
    return nullptr;
}
