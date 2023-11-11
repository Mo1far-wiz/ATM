#pragma once
#include "Card.h"

class CreditCard : public Card {
public:
	CreditCard(const size_t id, const std::string& cardNumber,
		const std::string& cvv, const size_t ownerId, const double currentBalance,
		const size_t expireDate, const float transactionCommission,
		const float witdrawCommission, const size_t creditLimit, const std::string& pin)
		: Card(id, cardNumber, cvv, ownerId, currentBalance, expireDate, CardType::Credit, transactionCommission, witdrawCommission, pin),
		_creditLimit(creditLimit)
	{}

	size_t GetCreditLimit() const {
		return _creditLimit;
	}
	virtual std::string ToString() const override {
		return "[CreditCard]: Id: " + std::to_string(_id) + " Number: " + _cardNumber + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv + " creditLimit: " + _creditLimit;
	}
private:
	size_t _creditLimit;
};
