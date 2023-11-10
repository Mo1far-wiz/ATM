#include <iostream>
#include <utility>
#include "CVV.h"
#include "CardType.h"

struct Card {
    size_t id;
    std::string cardNumber;
    size_t currentBalance;
    CVV cvv;
    size_t expireDate;
    CardType cardType;
    [[nodiscard]] virtual size_t GetTransactionCommission() const = 0;
    [[nodiscard]] virtual size_t GetWithdrawCommission() const = 0;
    Card(size_t id, std::string cardNumber, size_t currentBalance, const CVV& cvv,
         size_t expireDate, const CardType& cardType)
            : id(id), cardNumber(std::move(cardNumber)), currentBalance(currentBalance),
              cvv(cvv), expireDate(expireDate), cardType(cardType) {}
    virtual ~Card() {}
};
