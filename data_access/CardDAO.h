//
// Created by Oleksandr on 05.11.2023.
//

#ifndef ATM_CARDDAO_H
#define ATM_CARDDAO_H

#include <iostream>
#include <QtSql/QSqlQuery>
#include <QtCore/QObject>
#include "Cards/Card.h"

class CardDAO {

public:
    static CardDAO& getInstance();

    Card* getById(const QString& id) const;
    Card* getByCardNum(const QString& id) const;

    void createCard(const Card& card) const;

private:
    static void initialize();

    Card* deserializeCard(QSqlQuery &query) const;

    CardDAO() = default;
};


#endif //ATM_CARDDAO_H
