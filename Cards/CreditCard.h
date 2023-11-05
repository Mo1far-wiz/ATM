#include "Card.h"

class CreditCard : Card {
    size_t creditLimit;
    virtual size_t GetTransactionComission() const override {};
    virtual size_t GetWidthdrawComission() const override;
};


