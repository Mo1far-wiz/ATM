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

    [[nodiscard]] uint32_t getAvailableMoney(const uint32_t &id = 0) const;
    [[nodiscard]] ATM* getAtmById(const uint32_t &id = 0) const;

    void UpdateATM(const ATM& atm);

private:
    static void initialize();

    [[nodiscard]] ATM* deserializeATM(const QSqlQuery& executedQuery) const;

    ATM_DAO() = default;
};


#endif //ATM_ATM_DAO_H
