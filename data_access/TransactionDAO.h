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

    std::vector<Transaction> getCardTransactions(std::size_t cardId);
    std::vector<Transaction> getUserTransactions(std::size_t userId);

private:
    static void initialize();

    Transaction* deserializeTransaction(const QSqlQuery& query) const;
    TransactionDAO() = default;
};


#endif //ATM_TRANSACTIONDAO_H
