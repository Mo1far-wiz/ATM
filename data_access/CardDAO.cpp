//
// Created by Oleksandr on 05.11.2023.
//

#include "CardDAO.h"

#include <QDate>
#include <QDebug>
#include <QtSql>
#include <QtTest/qtestcase.h>

#include "Cards/CreditCard.h"
#include "Cards/DebitCard.h"

CardDAO &CardDAO::getInstance() {
    static CardDAO instance;
    initialize();
    return instance;
}

void CardDAO::initialize() {
    static bool isInitialized = false;
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    } else if (isInitialized) {
        qInfo() << "Database is already initialized.";
    }

    QSqlQuery createQuery("CREATE TABLE IF NOT EXISTS 'Card' "
                          "(id                      SERIAL          PRIMARY KEY, "
                          "cardNumber               CHAR(16)        NOT NULL, "
                          "cvv                      CHAR(3)         NOT NULL, "
                          "owner                    SERIAL          NOT NULL, "
                          "currentBalance           DOUBLE          NOT NULL, "
                          "expireDate               DATE            NOT NULL, "
                          "cardType_id              INTEGER         NOT NULL, "
                          "transactionCommission    FLOAT(1, 3)     NOT NULL, "
                          "withdrawCommission       FLOAT(1, 3)     NOT NULL, "
                          "creditLimit              INTEGER         NULL, "
                          "pin                      TEXT            NOT NULL, "
                          "FOREIGN KEY(cardType_id) REFERENCES CardType(id), "
                          "FOREIGN KEY(owner)       REFERENCES User(id));");

    qInfo() << "Creation of the 'Card' table was successful: " << createQuery.isActive();
    isInitialized = true;
}

Card *CardDAO::getById(const uint32_t &id) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Card WHERE id = :id");
    selectQuery.bindValue(":id", id);

    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            return deserializeCard(selectQuery);
        } else {
            qWarning() << "Card with " << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString()
                       << "not found.";
        }
    } else {
        qCritical() << "Error retrieving card:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}

Card *CardDAO::deserializeCard(const QSqlQuery &executedQuery) const {
    // Retrieve user data from the query result and create a Card object
    uint32_t id                     = executedQuery.value("id").toUInt();
    QString cardNumber              = executedQuery.value("cardNumber").toString();
    QString cvv                     = executedQuery.value("cvv").toString();
    uint32_t owner                  = executedQuery.value("owner").toUInt();
    double currentBalance           = executedQuery.value("currentBalance").toDouble();
    QDate expireDate                = executedQuery.value("expireDate").toDate();
    uint32_t cardType_id            = executedQuery.value("cardType_id").toUInt();
    float transactionCommission     = executedQuery.value("transactionCommission").toFloat();
    float withdrawCommission        = executedQuery.value("withdrawCommission").toFloat();
    uint creditLimit                = executedQuery.value("creditLimit").isNull() ?
                                                    0 : executedQuery.value("creditLimit").toUInt();
    QString pin                     = executedQuery.value("pin").toString();

    Card *card = nullptr;
    if (static_cast<CardType>(cardType_id) == CardType::Credit) {
        card = new CreditCard(id, cardNumber, cvv,
                              owner, currentBalance, expireDate,
                              transactionCommission,
                              withdrawCommission, creditLimit, pin);
    }
    else if (static_cast<CardType>(cardType_id) == CardType::Debit) {
        card = new DebitCard(id, cardNumber, cvv,
                             owner, currentBalance, expireDate,
                             transactionCommission,
                             withdrawCommission, creditLimit, pin);
    }
    qInfo() << "Card with ID" << id << "was found.";
    return card;
}

Card *CardDAO::getByCardNum(const QString &cardNum) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Card WHERE cardNumber = :cardNumber");
    selectQuery.bindValue(":cardNumber", cardNum);

    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            return deserializeCard(selectQuery);
        } else {
            qWarning() << "Card with " << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString()
                       << "not found.";
        }
    } else {
        qCritical() << "Error retrieving card:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}

Card *CardDAO::getByUserId(const uint32_t &id) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return nullptr;
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Card WHERE owner = :owner");
    selectQuery.bindValue(":owner", id);

    if (selectQuery.exec()) {
        if (selectQuery.next()) {
            return deserializeCard(selectQuery);
        } else {
            qWarning() << "Card with "
                       << selectQuery.boundValueName(0) << selectQuery.boundValue(0).toString()
                       << "not found.";
        }
    } else {
        qCritical() << "Error retrieving card:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return nullptr;
}

QList<Card *> CardDAO::multipleCardsDeserialization(QSqlQuery &executedQuery) const {
    QList<Card *> cards;

    while (executedQuery.next()) {
        Card *card = deserializeCard(executedQuery);
        if (card) {
            cards.append(card);
        } else {
            qWarning() << "Cards with " << executedQuery.boundValueName(0) << executedQuery.boundValue(0).toString()
                       << "not found.";
            break;
        }
    }

    return cards;
}

QList<Card *> CardDAO::getAllUserCards(const uint32_t &id) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return {};
    }

    // Prepare the SQL query
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM Card WHERE owner = :owner");
    selectQuery.bindValue(":owner", id);

    if (selectQuery.exec()) {
        return multipleCardsDeserialization(selectQuery);
    } else {
        qCritical() << "Error retrieving cards:" << selectQuery.lastError().text()
                    << "\n\t For query : " << selectQuery.lastQuery();
    }
    return {};
}

void CardDAO::addCard(const int id, const QString &cardNumber, const QString &cvv, uint32_t owner, double currentBalance,
                      const QDate &expireDate, int cardTypeId, float transactionCommission,
                      float withdrawCommission, int creditLimit, const QString &pin) const {
    if (!QSqlDatabase::database().isOpen()) {
        qCritical() << "Database is not open.";
        return;
    }

    // Prepare the SQL query
    QSqlQuery insertCardQuery;
    insertCardQuery.prepare("INSERT INTO Card (id, cardNumber, cvv, owner, currentBalance, expireDate, "
                            "cardType_id, transactionCommission, withdrawCommission, creditLimit, pin) "
                            "VALUES (:id, :cardNumber, :cvv, :owner, :currentBalance, :expireDate, "
                            ":cardTypeId, :transactionCommission, :withdrawCommission, :creditLimit, :pin)");
    insertCardQuery.bindValue(":id", id);
    insertCardQuery.bindValue(":cardNumber", cardNumber);
    insertCardQuery.bindValue(":cvv", cvv);
    insertCardQuery.bindValue(":owner", owner);
    insertCardQuery.bindValue(":currentBalance", currentBalance);
    insertCardQuery.bindValue(":expireDate", expireDate.toString(Qt::ISODate));
    insertCardQuery.bindValue(":cardTypeId", cardTypeId);
    insertCardQuery.bindValue(":transactionCommission", transactionCommission);
    insertCardQuery.bindValue(":withdrawCommission", withdrawCommission);
    insertCardQuery.bindValue(":creditLimit", creditLimit);
    insertCardQuery.bindValue(":pin", pin);

    // Execute the query
    if (insertCardQuery.exec()) {
        qInfo() << "Card with cardNumber" << cardNumber << "added successfully.";
    } else {
        qCritical() << "Error adding card:" << insertCardQuery.lastError().text()
                    << "\n\t For query : " << insertCardQuery.lastQuery();
    }
}

void CardDAO::UpdateCard(const Card *card) {
    if (!card || !card->GetId()) {
        qWarning() << "Invalid card object or card ID.";
        return;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE Card SET "
                        "cardNumber = :cardNumber, "
                        "cvv = :cvv, "
                        "owner = :owner, "
                        "currentBalance = :currentBalance, "
                        "expireDate = :expireDate, "
                        "cardType_id = :cardType_id, "
                        "transactionCommission = :transactionCommission, "
                        "withdrawCommission = :withdrawCommission, "
                        "creditLimit = :creditLimit, "
                        "pin = :pin "
                        "WHERE id = :id");

    updateQuery.bindValue(":cardNumber", card->GetCardNumber());
    updateQuery.bindValue(":cvv", card->GetCVV());
    updateQuery.bindValue(":owner", card->GetOwnerId());
    updateQuery.bindValue(":currentBalance", card->GetCurrentBalance());
    updateQuery.bindValue(":expireDate", card->GetExpireDate());
    updateQuery.bindValue(":cardType_id", static_cast<int>(card->GetCardType()));
    updateQuery.bindValue(":transactionCommission", card->GetTransactionCommission());
    updateQuery.bindValue(":withdrawCommission", card->GetWithdrawCommission());
    updateQuery.bindValue(":creditLimit", 0);
    updateQuery.bindValue(":pin", card->GetPinCode());
    updateQuery.bindValue(":id", card->GetId());

    if (updateQuery.exec()) {
        qDebug() << "Card with ID" << card->GetId() << "successfully updated.";
    } else {
        qCritical() << "Error updating card:" << updateQuery.lastError().text()
                    << "\n\t For query : " << updateQuery.lastQuery();
    }
}

