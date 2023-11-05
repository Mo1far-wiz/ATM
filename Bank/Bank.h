#include <iostream>

class ATM;
class Transaction;
class Card;
class User;

class Bank {
// [Method] Process transaction
    void ProcessTransaction(const Transaction& t);
    // [Method] Create ATM
    ATM CreateATM();
    // [Method] Delete ATM
    void DeleteATM(const size_t atmId);
    // [Method] Add new user
    void AddUser(const std::string& name, const std::string& surname);
    // [Method] Delete user
    void DeleteUser(const size_t userId);
    // [Method] Get user
    User GetUser(const size_t userId);
    // [Method] Add card for user
    void AddCard(const size_t userId);
    // [Method] Remove card
    void RemoveCard(const size_t cardId);
    // [Method] Get user's cards
    std::vector<Card*> GetCards(const size_t userId);
    // [Method] Get transactions history by user
    std::vector<Transaction> GetTransactionsHistoryByUser(const size_t userId);
    // [Method] Get transactions history by card
    std::vector<Transaction> GetTransactionsHistoryByCard(const size_t cardId);
    // [Method] Get user balance
    size_t GetUserBalance(const size_t userId);
    // [Method] Get card balance
    size_t GetCardBalance(const size_t cardId);
    // todo: add sql
};