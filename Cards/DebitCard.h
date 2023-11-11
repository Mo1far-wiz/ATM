#pragma once
#include "Card.h"

class DebitCard : public Card {
public:
	DebitCard(const size_t id, const std::string& cardNumber,
		const std::string& cvv, const size_t ownerId, const double currentBalance,
		const size_t expireDate, const float transactionCommission,
		const float witdrawCommission, const size_t creditLimit, const std::string& pin)
		: Card(id, cardNumber, cvv, ownerId, currentBalance, expireDate, CardType::Debit, transactionCommission, witdrawCommission, pin)
	{}

	virtual std::string ToString() const {
		return "[DebitCard]: Id: " + std::to_string(_id) + " Number: " + _cardNumber + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv;
	}
};