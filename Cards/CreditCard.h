#pragma once
#include "Card.h"

class CreditCard : public Card {
public:
	CreditCard(const uint32_t id, const QString& cardNumber,
               const QString& cvv, const uint32_t ownerId, const double currentBalance,
               const QDate& expireDate, const float transactionCommission,
               const float withdrawCommission, const double creditLimit, const QString& pin)
		: Card(id, cardNumber, cvv, ownerId, currentBalance, expireDate, CardType::Credit, transactionCommission, withdrawCommission, pin),
		_creditLimit(creditLimit){}

	uint32_t GetCreditLimit() const {
		return _creditLimit;
	}
	double GetDebt() const {
		double debt = GetCreditLimit() - GetBalance();
		return debt > 0 ? debt : 0;
	}
	virtual QString ToString() const override {
		return ("[CreditCard]: Id: " + std::to_string(_id) + ", Number: " + _cardNumber.toStdString() + ", OwnerId: " + std::to_string(_ownerId) + ", cvv: " + _cvv.toStdString() + ", creditLimit: " + std::to_string(_creditLimit)
		+ ", debt: " + std::to_string(GetDebt())).c_str();
	}
private:
    const double _creditLimit;
};
