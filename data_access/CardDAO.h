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

class CardDAO {

public:
    static CardDAO& getInstance();

    [[nodiscard]] Card* getById(const uint32_t &id) const;
    [[nodiscard]] Card* getByCardNum(const QString& cardNum) const;
    [[nodiscard]] Card* getByUserId(const uint32_t &id) const;
    [[nodiscard]] QList<Card*> getAllUserCards(const uint32_t &id) const;

    void addCard(const int id, const QString &cardNumber, const QString &cvv, uint32_t owner, double currentBalance,
                          const QDate &expireDate, int cardTypeId, float transactionCommission,
                          float withdrawCommission, int creditLimit, const QString &pin) const;
private:
    static void initialize();

    Card* deserializeCard(const QSqlQuery &executedQuery) const;
    QList<Card*> multipleCardsDeserialization(QSqlQuery &executedQuery) const;

    CardDAO() = default;
};


#endif //ATM_CARDDAO_H
