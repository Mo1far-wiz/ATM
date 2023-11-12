#pragma once
#include <iostream>
#include <utility>
#include <QDate>
#include "../IId.h"
#include "CardType.h"
#include "data_access/CardDAO.h"

class CardDAO;

class Card : IId {
public:
	using DAO = CardDAO;
    uint32_t GetId() const override {
		return _id;
	}
	QString GetCardNumber() const {
		return _cardNumber;
	}
	double GetBalance() const {
		return _currentBalance;
	}
	const QString& GetCVV() const {
		return _cvv;
	}
	const QString& GetPinCode() const {
		return _pinCode;
	}
    QDate GetExpireDate() const {
		return _expireDate;
	}
	CardType GetCardType() const {
		return _cardType;
	}
    uint32_t GetOwnerId() const {
		return _ownerId;
	}
	float GetTransactionCommission() const {
		return _transactionCommission;
	}
	float GetWithdrawCommission() const {
		return _withdrawCommission;
	}
	virtual ~Card() {}

	virtual QString ToString() const {
		return ("[Card]: Id: " + std::to_string(_id) + " Number: " + _cardNumber.toStdString() + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv.toStdString()).c_str();
	}

protected:
	Card(const uint32_t id, const QString& cardNumber,
         const QString& cvv, const uint32_t ownerId, const double currentBalance,
         const QDate& expireDate, const CardType cardType, const float transactionCommission,
         const float withdrawCommission, const QString& pin)
		: _id(id), _cardNumber(cardNumber), _cvv(cvv), _ownerId(ownerId), _currentBalance(currentBalance),
          _expireDate(expireDate), _cardType(cardType), _transactionCommission(transactionCommission),
          _withdrawCommission(withdrawCommission), _pinCode(pin)
	{}

protected:
	QString _cardNumber;
    QString _cvv;
    QString _pinCode;
	double _currentBalance;
	float _transactionCommission;
	float _withdrawCommission;
	QDate _expireDate;
    uint32_t _ownerId;
	const uint32_t _id;
	CardType _cardType;
};