//
// Created by Oleksandr on 05.11.2023.
//

#ifndef ATM_USERDAO_H
#define ATM_USERDAO_H

#include <iostream>
#include <QtSql/QSqlQuery>
#include <QtCore/QObject>

#include "User/User.h"

class UserDAO {
public:
    static UserDAO& getInstance();

    User* getById(uint32_t id) const;
    User* getByPhoneNum(const QString& phoneNum) const;
    User* getByCardNum(const QString& cardNum) const;
    QList<Card*> getAllUserCards(uint32_t userId);

    static void addUser(uint32_t id, const QString &name, const QString &surname, const QString &phoneNum);

private:
    static void initialize();

    [[nodiscard]] User* deserializeUser(QSqlQuery& query) const;

    UserDAO() = default;

};


#endif //ATM_USERDAO_H
