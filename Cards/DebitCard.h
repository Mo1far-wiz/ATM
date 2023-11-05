#include "Card.h"


struct DebitCard : Card{
    virtual size_t GetTransactionComission() const override {};
    virtual size_t GetWidthdrawComission() const override;
};


