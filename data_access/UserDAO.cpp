//
// Created by Oleksandr on 05.11.2023.
//

#include "UserDAO.h"
#include "CardDAO.h"

#include <QDebug>
#include <QtSql>
#include <QtTest/qtestcase.h>

uint32_t UserDAO::_id = 0;

UserDAO &UserDAO::getInstance() {
    static UserDAO instance;
    static bool isInitialized = false;
    if (!isInitialized)
    {
        initialize();
    }
    isInitialized = true;
    return instance;
}

void UserDAO::initialize() {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'User' "
                          "(id SERIAL PRIMARY KEY, "
                          "name TEXT NOT NULL, "
                          "surname TEXT NOT NULL, "
                          "phoneNum VARCHAR(13) NOT NULL);");

    qInfo() << "Creation of the 'User' table was successful: \t" << createQuery.isActive();
}

void UserDAO::addUser(const User* user) {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    }
    else if (!user)
    {
        qCritical() << "Can't add user, user is null.";
        return;
    }

    // Prepare the SQL query
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO User (id, name, surname, phoneNum) VALUES (:id, :name, :surname, :phoneNum)");
    insertQuery.bindValue(":id", _id++);
    insertQuery.bindValue(":name", user->GetName());
    insertQuery.bindValue(":surname", user->GetSurname());
    insertQuery.bindValue(":phoneNum", user->GetPhoneNumber());

    // Execute the query
    if (insertQuery.exec()) {
        qInfo() << "User with ID " << _id-1 << " added successfully.";
    } else {
        qCritical() << "Error adding user:" << insertQuery.lastError().text()
                    << "\n\t For query : " << insertQuery.lastQuery();
    }
}


User *UserDAO::deserializeUser(QSqlQuery &selectQuery) const{
    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            // Retrieve user data from the query result and create a User object
            uint32_t id         = selectQuery.value("id").toUInt();
            QString name        = selectQuery.value("name").toString();
            QString surname     = selectQuery.value("surname").toString();
            QString phoneNum    = selectQuery.value("phoneNum").toString();

            User* user = new User(id, name, surname, phoneNum);
            qInfo() << "User with ID" << id << "was found.";
            return user;
        } else {
            qWarning() << "User with " << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString() << "not found.";
        }
    } else {
        qCritical() << "Error retrieving user:" << selectQuery.lastError().text()
        <<"\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}
User* UserDAO::getById(const uint32_t &id) const{
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM User WHERE id = :id");
    selectQuery.bindValue(":id", id);

    return deserializeUser(selectQuery);
}

User *UserDAO::getByPhoneNum(const QString& phoneNum) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM User WHERE phoneNum = :phoneNum");
    selectQuery.bindValue(":phoneNum", phoneNum);

    return deserializeUser(selectQuery);
}

User *UserDAO::getByCardNum(const QString& cardNum) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    if(Card* card = CardDAO::getInstance().getByCardNum(cardNum)) {
        // Prepare the SQL query
        QSqlQuery selectQuery;
        selectQuery.prepare("SELECT * FROM User WHERE id = :id");
        selectQuery.bindValue(":id", card->GetOwnerId());

        return deserializeUser(selectQuery);
    }

    return nullptr;
}

QList<Card *> UserDAO::getAllUserCards(const uint32_t &userId) const{
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return {};
    }

    return CardDAO::getInstance().getAllUserCards(userId);
}

