#include <iostream>
#include "CVV.h"
#include "CardType.h"

struct Card {
    size_t id;
    std::string cardNumber;
    size_t currentBalance;
    CVV cvv;
    size_t expireDate;
    CardType cardType;
    virtual size_t GetTransactionComission() const = 0;
    virtual size_t GetWidthdrawComission() const = 0;
    virtual ~Card();
};
