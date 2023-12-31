//
// Created by Oleksandr on 05.11.2023.
//

#ifndef ATM_USERDAO_H
#define ATM_USERDAO_H

#include <iostream>
#include <QtSql/QSqlQuery>
#include <QtCore/QObject>

#include "User/User.h"

class User;

class UserDAO {
public:
    static UserDAO& getInstance();

    [[nodiscard]] User* getById(const uint32_t &id) const;
    [[nodiscard]] User* getByPhoneNum(const QString& phoneNum) const;
    [[nodiscard]] User* getByCardNum(const QString& cardNum) const;
    [[nodiscard]] QList<Card*> getAllUserCards(const uint32_t &userId) const;

    void addUser(const User* user);

private:
    static uint32_t _id;
    static void initialize();

    [[nodiscard]] User* deserializeUser(QSqlQuery& query) const;

    UserDAO() = default;

};


#endif //ATM_USERDAO_H
