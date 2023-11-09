//
// Created by Oleksandr on 05.11.2023.
//

#include "UserDAO.h"

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
                          "phoneNum VARCHAR(13) NOT NULL));");

    qDebug() << "creation of the 'User' table was successful: " << createQuery.isActive();
    isInitialized = true;
}
