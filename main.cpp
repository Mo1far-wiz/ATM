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

#include "Cards/DebitCard.h"

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

//        userDao.addUser(new User(1, "Frdy", "Fzber", "+1987"));
//        //User* user = userDao.getById(0);
//        //User* user2 = userDao.getByPhoneNum("+1987");
//
//        cardDao.addCard(new CreditCard(1,"1", "111", 1, 10, QDate::currentDate(), 0.01, 0.01, 100, "1111"));
//
//        ATM::getInstance().insertCard(cardDao.getById(1));
//
//        ATM::getInstance().withdrawMoney(10000);
//
//        std::cout << ATM::getInstance().getAvailableWithdraw() << std::endl;
//        cardDao.addCard(0, "1987", "111", 0, 14.88,
//                        QDate::currentDate(), 0, 0.1,
//                        0.3, 0,"123");
//        cardDao.addCard(1, "1983", "111", 0, 14.88,
//                        QDate::currentDate(), 1, 0.1,
//                        0.3, 0,"123");
//
//        User* user = userDao.getById(0);
//        Card* card1 = cardDao.getByUserId(0);
//        DebitCard* debit = dynamic_cast<DebitCard*>(card1);
//        cardDao.UpdateCard(*debit);
//        std::cout << (user ? user->toString().toStdString() : "") << std::endl;
//        std::cout << (card1 ? card1->ToString().toStdString() : "") << std::endl;
//        QList<Card*> cards = cardDao.getAllUserCards(0);
//        std::for_each(cards.begin(), cards.end(), [](Card* card){
//            std::cout << card->ToString().toStdString() << std::endl;
//        });
    }


    return a.exec();
}
