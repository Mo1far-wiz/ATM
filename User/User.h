#pragma once

#include <iostream>
#include <vector>
#include <QString>
#include <QtCore/QObject>

#include "Cards/Card.h"
#include "data_access/UserDAO.h"

class User : IId, public QObject {
public:
	User() = delete;
	User(const uint32_t id, const QString& name, const QString& surname, const QString& phoneNum)
		: _id(id), _name(name), _surname(surname), _phoneNum(phoneNum) {
    }
	~User() {}

	uint32_t GetId() const override {
		return _id;
	}
	const QString& GetName() const {
		return _name;
	}
	const QString& GetSurname() const {
		return _surname;
	}
	const QString& GetPhoneNumber() const {
		return _phoneNum;
	}
	QString ToString() const {
		return (("[User]: Id: " + std::to_string(_id) + " Name: " + _name.toStdString() + " Surname: " + _surname.toStdString() + " phone: " + _phoneNum.toStdString()).c_str());
	}

	QList<std::shared_ptr<Card>> getUserCards() const {
		QList<std::shared_ptr<Card>> l;
		for (Card* card : CardDAO::getInstance().getAllUserCards(GetId())) {
			if (!card) { return QList<std::shared_ptr<Card>>(); }
			l.push_back(std::shared_ptr<Card>(card));
		}
		return l;
	}

private:
	QString _name;
	QString _surname;
	QString _phoneNum;
	const uint32_t _id;
};

