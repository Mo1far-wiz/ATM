#include "Card.h"


struct DebitCard : Card{
    virtual size_t GetTransactionCommission() const override {}
    virtual size_t GetWithdrawCommission() const override {}
};


