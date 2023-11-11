//
// Created by Oleksandr on 05.11.2023.
//

#ifndef ATM_ATM_DAO_H
#define ATM_ATM_DAO_H

#include <iostream>
#include <QtSql/QSqlQuery>
#include <QtCore/QObject>

#include "Bank/ATM.h"

class ATM_DAO {
public:
    static ATM_DAO& getInstance();

    std::size_t getAvailableMoney();
private:
    static void initialize();

    ATM* deserializeATM(const QSqlQuery& query) const;

    ATM_DAO() = default;
};


#endif //ATM_ATM_DAO_H
