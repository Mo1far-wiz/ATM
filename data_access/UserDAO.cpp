//
// Created by Oleksandr on 05.11.2023.
//

#include "UserDAO.h"
#include "CardDAO.h"

#include <QDebug>
#include <QtSql>
#include <QtTest/qtestcase.h>



UserDAO &UserDAO::getInstance() {
    static UserDAO instance;
    initialize();
    return instance;
}

void UserDAO::initialize() {
    static bool isInitialized = false;
    if (isInitialized || !QSqlDatabase::database().isOpen()) {
        return;
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'User' "
                          "(id SERIAL PRIMARY KEY, "
                          "name TEXT NOT NULL, "
                          "surname TEXT NOT NULL, "
                          "phoneNum VARCHAR(13) NOT NULL);");

    qInfo() << "creation of the 'User' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

void UserDAO::addUser(uint32_t id, const QString &name, const QString &surname, const QString &phoneNum) {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    }

    // Prepare the SQL query
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO User (id, name, surname, phoneNum) VALUES (:id, :name, :surname, :phoneNum)");
    insertQuery.bindValue(":id", id);
    insertQuery.bindValue(":name", name);
    insertQuery.bindValue(":surname", surname);
    insertQuery.bindValue(":phoneNum", phoneNum);

    // Execute the query
    if (insertQuery.exec()) {
        qInfo() << "User added successfully.";
    } else {
        qCritical() << "Error adding user:" << insertQuery.lastError().text();
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

            User* user = new User(id, name.toStdString(), surname.toStdString(), phoneNum.toStdString());
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
User* UserDAO::getById(uint32_t id) const{
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
        selectQuery.bindValue(":id", (uint32_t)card->id);   // change to user id

        return deserializeUser(selectQuery);
    }

    return nullptr;
}

QList<Card *> UserDAO::getAllUserCards(uint32_t userId) {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return {};
    }

    return CardDAO::getInstance().getAllUserCards(userId);
}

