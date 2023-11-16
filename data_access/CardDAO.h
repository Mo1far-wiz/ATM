//
// Created by Oleksandr on 05.11.2023.
//

#ifndef ATM_CARDDAO_H
#define ATM_CARDDAO_H

#include <iostream>
#include <QtSql/QSqlQuery>
#include <QtCore/QObject>

#include "Cards/Card.h"

class Card;
class CreditCard;
class DebitCard;

class CardDAO {

public:
    static CardDAO& getInstance();

    [[nodiscard]] Card* getById(const uint32_t &id) const;
    [[nodiscard]] Card* getByCardNum(const QString& cardNum) const;
    [[nodiscard]] Card* getByUserId(const uint32_t &id) const;
    [[nodiscard]] QList<Card*> getAllUserCards(const uint32_t &id) const;

    void UpdateCard(const DebitCard& card);
    void UpdateCard(const CreditCard& card);

    void addCard(Card *card) const;
private:
    static void initialize();

    Card* deserializeCard(const QSqlQuery &executedQuery) const;
    QList<Card*> multipleCardsDeserialization(QSqlQuery &executedQuery) const;

    void UpdateCard(const Card *card, const uint32_t& creditLimit = 0);

        CardDAO() = default;
};


#endif //ATM_CARDDAO_H
