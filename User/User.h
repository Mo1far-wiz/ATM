#include <iostream>
#include <vector>
#include <QString>
#include <QtCore/QObject>

#include "Cards/Card.h"

class Card;

struct User {
    User(const uint32_t id, const QString& name, const QString& surname, const QString& phoneNum)
            : id(id), name(name), surname(surname), phoneNum(phoneNum) {

    }
    ~User() {}
    uint32_t id;
    QString name;
    QString surname;
    QString phoneNum;
    QList<Card*> cards;

    QString toString() const {
        std::string result;

        result += "ID: " + std::to_string(id) + "\n";
        result += "Name: " + name.toStdString() + "\n";
        result += "Surname: " + surname.toStdString() + "\n";
        result += "Phone Number: " + phoneNum.toStdString() + "\n";
        result += "Cards: ";

        for (auto card: cards) {
            result += card->ToString().toStdString() + " ";
        }
        result += "\n";

        return result.c_str();
    }


};

