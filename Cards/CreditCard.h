#pragma once
#include "Card.h"

class CreditCard : public Card {
public:
	CreditCard(const uint32_t id, const std::string& cardNumber,
               const std::string& cvv, const uint32_t ownerId, const double currentBalance,
               const uint32_t expireDate, const float transactionCommission,
               const float withdrawCommission, const uint32_t creditLimit, const std::string& pin)
		: Card(id, cardNumber, cvv, ownerId, currentBalance, expireDate, CardType::Credit, transactionCommission, withdrawCommission, pin),
		_creditLimit(creditLimit)
	{}

	size_t GetCreditLimit() const {
		return _creditLimit;
	}
	virtual std::string ToString() const override {
		return "[CreditCard]: Id: " + std::to_string(_id) + " Number: " + _cardNumber + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv + " creditLimit: " + std::to_string(_creditLimit);
	}
private:
	size_t _creditLimit;
};
