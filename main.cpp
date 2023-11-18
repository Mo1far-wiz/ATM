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

void initDB() {
    ATM_DAO& atmDao                 = ATM_DAO::getInstance();
    UserDAO& userDao                = UserDAO::getInstance();
    CardDAO& cardDao                = CardDAO::getInstance();
    TransactionDAO& transactionDao  = TransactionDAO::getInstance();

    // bank
    User* bank = new User(0, "Bank", "Bank", "+000");
    userDao.addUser(bank);
    DebitCard* debitBank   = new DebitCard (0, "0", "000", 0, 0, QDate::currentDate().addDays(10), 0, 0, 0, "000");
    cardDao.addCard(debitBank);

    // add 3 users
    User* user1 = new User(1, "1Freddy", "1Fazbear", "+1987");
    User* user2 = new User(2, "2Bonnie", "2TheBunny", "+1983");
    User* user3 = new User(3, "3Foxy", "3Tvar", "+1488");

    userDao.addUser(user1);
    userDao.addUser(user2);
    userDao.addUser(user3);

    // add 2 cards to each user
    DebitCard* debit1   = new DebitCard (1, "11", "111", 1, 1987, QDate::currentDate().addDays(10), 0.01, 0.02, 0, "111");
    CreditCard* credit1 = new CreditCard(2, "12", "111", 1, 1987 + 1000, QDate::currentDate().addDays(10), 0.02, 0.03, 1000, "111");

    DebitCard* debit2   = new DebitCard (3, "21", "111", 2, 1987, QDate::currentDate().addDays(10), 0.01, 0.02, 0, "111");
    CreditCard* credit2 = new CreditCard(4, "22", "111", 2, 1987 + 2000, QDate::currentDate().addDays(10), 0.02, 0.03, 2000, "111");

    DebitCard* debit3   = new DebitCard (5, "31", "111", 3, 1987, QDate::currentDate().addDays(10), 0.01, 0.02, 0, "111");
    CreditCard* credit3 = new CreditCard(6, "32", "111", 3, 1987 + 3000, QDate::currentDate().addDays(10), 0.02, 0.03, 3000, "111");

    cardDao.addCard(debit1);
    cardDao.addCard(credit1);

    cardDao.addCard(debit2);
    cardDao.addCard(credit2);

    cardDao.addCard(debit3);
    cardDao.addCard(credit3);

    // add transaction for this cards
    Transaction* transaction12 = new Transaction(1, 1, 2, 1.2);
    Transaction* transaction13 = new Transaction(2, 1, 3, 1.3);
    Transaction* transaction15 = new Transaction(3, 1, 5, 1.5);
    transactionDao.addTransaction(transaction12);
    transactionDao.addTransaction(transaction13);
    transactionDao.addTransaction(transaction15);

    Transaction* transaction21 = new Transaction(4, 2, 1, 2.1);
    Transaction* transaction24 = new Transaction(5, 2, 4, 2.4);
    Transaction* transaction26 = new Transaction(6, 2, 6, 2.6);
    transactionDao.addTransaction(transaction21);
    transactionDao.addTransaction(transaction24);
    transactionDao.addTransaction(transaction26);

    Transaction* transaction34 = new Transaction(7, 3, 4, 3.4);
    Transaction* transaction32 = new Transaction(8, 3, 2, 3.2);
    Transaction* transaction35 = new Transaction(9, 3, 5, 3.5);
    transactionDao.addTransaction(transaction34);
    transactionDao.addTransaction(transaction32);
    transactionDao.addTransaction(transaction35);

    Transaction* transaction41 = new Transaction(10, 4, 1, 4.1);
    Transaction* transaction45 = new Transaction(11, 4, 5, 4.5);
    Transaction* transaction46 = new Transaction(12, 4, 6, 4.6);
    transactionDao.addTransaction(transaction41);
    transactionDao.addTransaction(transaction45);
    transactionDao.addTransaction(transaction46);

    Transaction* transaction51 = new Transaction(13, 5, 1, 5.1);
    Transaction* transaction52 = new Transaction(14, 5, 2, 5.2);
    Transaction* transaction53 = new Transaction(15, 5, 3, 5.3);
    transactionDao.addTransaction(transaction51);
    transactionDao.addTransaction(transaction52);
    transactionDao.addTransaction(transaction53);

    Transaction* transaction64 = new Transaction(16, 6, 4, 6.4);
    Transaction* transaction65 = new Transaction(17, 6, 5, 6.5);
    Transaction* transaction63 = new Transaction(18, 6, 3, 6.3);
    transactionDao.addTransaction(transaction64);
    transactionDao.addTransaction(transaction65);
    transactionDao.addTransaction(transaction63);

    // Delete dynamically allocated objects
    delete bank;
    delete debitBank;
    delete user1;
    delete user2;
    delete user3;
    delete debit1;
    delete credit1;
    delete debit2;
    delete credit2;
    delete debit3;
    delete credit3;
    delete transaction12;
    delete transaction13;
    delete transaction15;
    delete transaction21;
    delete transaction24;
    delete transaction26;
    delete transaction34;
    delete transaction32;
    delete transaction35;
    delete transaction41;
    delete transaction45;
    delete transaction46;
    delete transaction51;
    delete transaction52;
    delete transaction53;
    delete transaction64;
    delete transaction65;
    delete transaction63;
}

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
        initDB();
        });
    }


    return a.exec();
}