//
// Created by Oleksandr on 05.11.2023.
//
#include <QSqlDatabase>
#include "TransactionDAO.h"

TransactionDAO &TransactionDAO::getInstance() {
    static TransactionDAO instance;
    initialize();
    return instance;
}

void TransactionDAO::initialize() {
    static bool isInitialized = false;
    if (isInitialized || !QSqlDatabase::database().isOpen()) {
        return;
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'Transaction' "
                          "(id INTEGER PRIMARY KEY, "
                          "fromCardId INT NOT NULL, "
                          "toCardId INT NOT NULL, "
                          "amount INT NOT NULL, "
                          "FOREIGN KEY(fromCardId) REFERENCES Card(id), "
                          "FOREIGN KEY(toCardId) REFERENCES Card(id));");


    qDebug() << "creation of the 'Transaction' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

Transaction *TransactionDAO::deserializeTransaction(const QSqlQuery &query) const {
    return nullptr;
}
