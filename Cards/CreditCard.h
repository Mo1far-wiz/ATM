#include "Card.h"

class CreditCard : Card {
    size_t creditLimit;
    virtual size_t GetTransactionCommission() const override{}
    virtual size_t GetWithdrawCommission() const override{}
};


