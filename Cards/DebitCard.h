#include "Card.h"

struct DebitCard : public Card {
    DebitCard(size_t id, const std::string& cardNumber, size_t currentBalance, const CVV& cvv,
              size_t expireDate, const CardType& cardType)
            : Card(id, cardNumber, currentBalance, cvv, expireDate, cardType) {}

    virtual size_t GetTransactionCommission() const override {
        return 1;
    }

    virtual size_t GetWithdrawCommission() const override {
        return 2;
    }
};
