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

    Card* getById(uint32_t id) const;
    Card* getByCardNum(const QString& cardNum) const;
    Card* getByUserId(uint32_t id) const;
    QList<Card*> getAllUserCards(uint32_t id) const;

    void addCard(const Card& card) const;

private:
    static void initialize();

    Card* deserializeCard(QSqlQuery &executedQuery) const;
    QList<Card*> multipleCardsDeserialization(QSqlQuery &executedQuery) const;

    CardDAO() = default;
};


#endif //ATM_CARDDAO_H
