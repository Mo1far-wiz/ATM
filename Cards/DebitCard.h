#pragma once
#include "Card.h"

class DebitCard : public Card {
public:
	DebitCard(const uint32_t id, const QString& cardNumber,
              const QString& cvv, const uint32_t ownerId, const double currentBalance,
              const QDate& expireDate, const float transactionCommission,
              const float withdrawCommission, const uint32_t creditLimit, const QString& pin)
		: Card(id, cardNumber, cvv, ownerId, currentBalance, expireDate, CardType::Debit, transactionCommission, withdrawCommission, pin)
	{}

	virtual QString ToString() const {
		return ("[DebitCard]: Id: " + std::to_string(_id) + " Number: " + _cardNumber.toStdString() + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv.toStdString()).c_str();
	}
};