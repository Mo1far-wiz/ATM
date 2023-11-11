#pragma once
#include "Card.h"

class DebitCard : public Card {
public:
	DebitCard(const uint32_t id, const std::string& cardNumber,
              const std::string& cvv, const uint32_t ownerId, const double currentBalance,
              const uint32_t expireDate, const float transactionCommission,
              const float withdrawCommission, const uint32_t creditLimit, const std::string& pin)
		: Card(id, cardNumber, cvv, ownerId, currentBalance, expireDate, CardType::Debit, transactionCommission, withdrawCommission, pin)
	{}

	virtual std::string ToString() const {
		return "[DebitCard]: Id: " + std::to_string(_id) + " Number: " + _cardNumber + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv;
	}
};