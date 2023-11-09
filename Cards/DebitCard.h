#include "Card.h"


struct DebitCard : Card{
    virtual size_t GetTransactionCommission() const override {
        return 1;
    }
    virtual size_t GetWithdrawCommission() const override {
        return 2;
    }
};


