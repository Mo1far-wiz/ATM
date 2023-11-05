#include <iostream>

class Bank;
class Card;
struct CVV;

class ATM {
    ATM(Bank& bank) : _bankRef(bank) {
    }
    ~ATM() {}
    // Id
    size_t id;
    // Bank id
    size_t bankId;
    // Amount of money left to withdraw
    size_t moneyLeft;
    // Currently inserted card
    size_t currentCardId;
    // [Method] Insert & Verify card
    void AcceptCard(const Card&);
    // [Method] Create a transaction and make Bank process it
    void CreateTransaction(const Card& from, const Card& to, size_t amount);
    // [Method] Check balance
    size_t GetBalance();
    // [Method] Change CVV
    void ChangeCVV(const CVV oldCvv);
private:
    Bank& _bankRef;
};