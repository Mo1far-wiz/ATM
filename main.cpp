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

    qDebug()  <<  QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../db_file/db_bank.sqlite");
    if (!db.open()) {
        qDebug() << db.lastError().text();
        return -1;
    } else {
        // trigger initializations after the db connection is established
        ATM_DAO::getInstance();
        UserDAO::getInstance();
        CardDAO::getInstance();
        TransactionDAO::getInstance();
    }


    return a.exec();
}
