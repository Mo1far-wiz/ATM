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

    QList<Transaction *> getCardTransactions(uint32_t cardId);
    QList<Transaction*> getUserTransactions(uint32_t userId);

private:
    static void initialize();

    Transaction* deserializeTransaction(const QSqlQuery& executedQuery) const;
    QList<Transaction *> multipleCardsDeserialization(QSqlQuery &executedQuery) const;

    TransactionDAO() = default;
};


#endif //ATM_TRANSACTIONDAO_H
