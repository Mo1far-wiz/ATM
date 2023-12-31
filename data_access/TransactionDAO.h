//
// Created by Oleksandr on 05.11.2023.
//

#ifndef ATM_TRANSACTIONDAO_H
#define ATM_TRANSACTIONDAO_H

#include <iostream>
#include <QtSql/QSqlQuery>
#include <QtCore/QObject>

#include "Bank/Transaction.h"

class TransactionDAO {
public:
    static TransactionDAO& getInstance();

    [[nodiscard]] QList<Transaction*> getCardTransactions(const uint32_t &cardId) const;
    [[nodiscard]] QList<Transaction*> getUserTransactions(const uint32_t &userId) const;

    void addTransaction(const Transaction* transaction) const;

private:
    static uint32_t _id;
    static void initialize();

    [[nodiscard]] Transaction* deserializeTransaction(const QSqlQuery& executedQuery) const;
    QList<Transaction *> multipleCardsDeserialization(QSqlQuery &executedQuery) const;

    TransactionDAO() = default;
};


#endif //ATM_TRANSACTIONDAO_H
