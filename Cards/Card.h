#pragma once
#include <iostream>
#include <utility>
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
	std::string GetCardNumber() const {
		return _cardNumber;
	}
	double GetCurrentBalance() const {
		return _currentBalance;
	}
	const std::string& GetCVV() const {
		return _cvv;
	}
	const std::string& GetPinCode() const {
		return _pinCode;
	}
    uint32_t GetExpireDate() const {
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

	virtual std::string ToString() const {
		return "[Card]: Id: " + std::to_string(_id) + " Number: " + _cardNumber + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv;
	}

protected:
	Card(const uint32_t id, const std::string& cardNumber,
         const std::string& cvv, const uint32_t ownerId, const double currentBalance,
         const uint32_t expireDate, const CardType cardType, const float transactionCommission,
         const float withdrawCommission, const std::string& pin)
		: _id(id), _cardNumber(cardNumber), _cvv(cvv), _ownerId(ownerId), _currentBalance(currentBalance),
          _expireDate(expireDate), _cardType(cardType), _transactionCommission(transactionCommission),
          _withdrawCommission(withdrawCommission), _pinCode(pin)
	{}

protected:
	std::string _cardNumber;
	std::string _cvv;
	std::string _pinCode;
	double _currentBalance;
	float _transactionCommission;
	float _withdrawCommission;
	uint32_t _expireDate;
    uint32_t _ownerId;
	const uint32_t _id;
	CardType _cardType;
};