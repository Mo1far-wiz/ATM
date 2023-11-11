//
// Created by Oleksandr on 05.11.2023.
//

#include "ATM_DAO.h"

#include <QDate>
#include <QDebug>
#include <QtSql>
#include <QtTest/qtestcase.h>

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
                          "(id              SERIAL      PRIMARY KEY, "
                          "bankId           SERIAL      NOT NULL, "
                          "currentBalance   INTEGER     NOT NULL, "
                          "moneyLeft        INTEGER     NOT NULL, "
                          "currentCardId    SERIAL      NULL,"
                          "FOREIGN KEY(currentCardId) REFERENCES Card(id));");

    qInfo() << "creation of the 'ATM' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

ATM *ATM_DAO::deserializeATM(const QSqlQuery &executedQuery) const {
    uint32_t id = executedQuery.value("id").toUInt();
    uint32_t bankId = executedQuery.value("bankId").toUInt();
    uint32_t currentBalance = executedQuery.value("currentBalance").toUInt();
    uint32_t moneyLeft = executedQuery.value("moneyLeft").toUInt();
    uint32_t currentCardId = executedQuery.value("currentCardId").isNull() ?
                                -1 : executedQuery.value("currentCardId").toUInt();

    ATM* atm = nullptr;
    qInfo() << "ATM with ID" << id << "was found.";
    return atm;
}

uint32_t ATM_DAO::getAvailableMoney(uint32_t id) {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return -1;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT moneyLeft FROM ATM WHERE id = :id");
    selectQuery.bindValue(":id", id);

    if (selectQuery.exec()) {
        return deserializeATM(selectQuery)->moneyLeft;
    } else {
        qCritical() << "Error retrieving transactions:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return -1;
}
