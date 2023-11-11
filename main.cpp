#include "mainwindow.h"
#include "data_access/IncludeDataAccess.h"
#include <iostream>
#include <QApplication>
#include <QSqlDatabase>
#include <QApplication>
#include <QtWidgets/QStyleFactory>
#include <QDebug>
#include <QtSql>
#include <QtTest/qtestcase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qInfo()  <<  QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../db_file/db_bank.sqlite");
    if (!db.open()) {
        qCritical() << db.lastError().text();
        return -1;
    } else {
        // trigger initializations after the db connection is established
        ATM_DAO::getInstance();
        UserDAO userDao = UserDAO::getInstance();
        CardDAO cardDao = CardDAO::getInstance();
        TransactionDAO::getInstance();

        //userDao.addUser(0, "Frdy", "Fzbr", "+1987");
        //User* user = userDao.getByPhoneNum("+1987");
        User* user = userDao.getById(0);
        std::cout << (user ? user->toString() : "") << std::endl;
        QList<Card*> cards = cardDao.getAllUserCards(100);
        std::for_each(cards.begin(), cards.end(), [](Card* card){
            std::cout << (int)card->cardType << std::endl;
        });
    }


    return a.exec();
}
