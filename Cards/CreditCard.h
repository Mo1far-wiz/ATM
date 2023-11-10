#include "Card.h"

class CreditCard : public Card {
private:
    size_t creditLimit;

public:
    CreditCard(size_t id, const std::string& cardNumber, size_t currentBalance, const CVV& cvv,
               size_t expireDate, const CardType& cardType, size_t creditLimit)
            : Card(id, cardNumber, currentBalance, cvv, expireDate, cardType), creditLimit(creditLimit) {}

    virtual size_t GetTransactionCommission() const override {
        return 1;
    }

    virtual size_t GetWithdrawCommission() const override {
        return 2;
    }
};
