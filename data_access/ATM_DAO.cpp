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
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    } else if (isInitialized) {
        qInfo() << "Database is already initialized.";
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'ATM' "
                          "(id              SERIAL      PRIMARY KEY, "
                          "bankId           SERIAL      NOT NULL, "
                          "moneyLeft        INTEGER     NOT NULL, "
                          "currentCardId    SERIAL      NULL,"
                          "FOREIGN KEY(currentCardId) REFERENCES Card(id));");

    qInfo() << "Creation of the 'ATM' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

ATM *ATM_DAO::deserializeATM(const QSqlQuery &executedQuery) const {
    uint32_t id             = executedQuery.value("id").toUInt();
    uint32_t bankId         = executedQuery.value("bankId").toUInt();
    uint32_t moneyLeft      = executedQuery.value("moneyLeft").toUInt();
    uint32_t currentCardId  = executedQuery.value("currentCardId").isNull() ?
                                    -1 : executedQuery.value("currentCardId").toUInt();

    ATM* atm = nullptr;
    qInfo() << "ATM with ID" << id << "was found.";
    return atm;
}

uint32_t ATM_DAO::getAvailableMoney(const uint32_t &id) {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return -1;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT moneyLeft FROM ATM WHERE id = :id");
    selectQuery.bindValue(":id", id);

    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            return deserializeATM(selectQuery)->moneyLeft;
        } else {
            qWarning() << "ATM with " << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString() << "not found.";
        }
    } else {
        qCritical() << "Error retrieving ATM:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return -1;
}

ATM *ATM_DAO::getAtmById(const uint32_t &id) const{
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT moneyLeft FROM ATM WHERE id = :id");
    selectQuery.bindValue(":id", id);

    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            return deserializeATM(selectQuery);
        } else {
            qWarning() << "ATM with " << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString() << "not found.";
        }
    } else {
        qCritical() << "Error retrieving ATM:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}

//void ATM_DAO::UpdateATM(const ATM &atm) const {
//    if (!QSqlDatabase::database().isOpen()) {
//        qCritical() << "Database is not open.";
//        return;
//    }
//
//    QSqlQuery updateQuery;
//    updateQuery.prepare("UPDATE ATM SET "
//                        "bankId = :bankId, "
//                        "moneyLeft = :moneyLeft, "
//                        "currentCardId = :currentCardId "
//                        "WHERE id = :id");
//
//    updateQuery.bindValue(":bankId", atm.getBankId());
//    updateQuery.bindValue(":moneyLeft", atm.getMoneyLeft());
//    updateQuery.bindValue(":currentCardId", atm.getCurrentCardId());
//    updateQuery.bindValue(":id", atm.getId());
//
//    if (updateQuery.exec()) {
//        qDebug() << "ATM with ID" << atm.getId() << "successfully updated.";
//    } else {
//        qCritical() << "Error updating ATM:" << updateQuery.lastError().text()
//                    << "\n\t For query : " << updateQuery.lastQuery();
//    }
//}
