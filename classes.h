#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>
#include <algorithm>
#include <memory>

class Bank;
class ATM;
struct User;
struct Card;
struct DebitCard;
struct Transaction;
struct CVV {
	uint8_t cvv[3];
};

struct User {
	User() {
		std::cout << "User default ctor()\n";
	}
	User(const size_t id, const std::string name, const std::string surname)
		: id(id), name(name), surname(surname) {
		std::cout << "User normal ctor()\n";
	}
	~User() {}
	size_t id;
	std::string name;
	std::string surname;
	std::string phoneNum;
	std::vector<size_t> cards;
};

enum class CardType {
	Debit, Credit
};

struct Card {
	size_t id;
	std::string cardNumber;
	size_t currentBalance;
	CVV cvv;
	size_t expireDate;
	CardType cardType;
	virtual size_t GetTransactionComission() const = 0;
	virtual size_t GetWidthdrawComission() const = 0;
	virtual ~Card() {};
};

struct DebitCard : Card {
	virtual size_t GetTransactionComission() const override { return 0; };
	virtual size_t GetWidthdrawComission() const override { return 0; };
};

struct CreditCard : Card {
	size_t creditLimit;
	virtual size_t GetTransactionComission() const override {};
	virtual size_t GetWidthdrawComission() const override;
};

struct Transaction {
	const size_t from;
	const size_t to;
	const size_t amount;
};


class ATM {
public:
	ATM(Bank& bank, size_t id) : _bankRef(bank), id(id) {

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

class Bank {
	// [Method] Process transaction
	void ProcessTransaction(const Transaction& t)
	{

	}

	/* --- ATM --- */
	ATM atm = ATM(*this, 0);

	/* --- Users --- */
	/*
		User* getById(std::size_t id) const;
		User* getByPhoneNum(std::string phoneNum) const;
		User* getByCardNum(std::string cardNumber) const;
		std::vector<std::size_t>* getUserCards(std::size_t userId);
	*/

	/*template <class T, class DAO>
	std::optional<T> GetSomething(const size_t id)
	{
		auto r = DAO::getInstance().getById();
	}*/

	// [Method] Get user by id
	std::optional<User> GetUserById(const size_t userId)
	{
		if (User* r = UserDAO::getInstance().getById(userId)) {
			User rr = std::move(*r);
			delete r;
			return rr;
		}
		return std::nullopt;
	}
	
	// [Method] Get user by phone number
	std::optional<User> GetUserByPhoneNum(const std::string& phoneNum)
	{
		if (User* r = UserDAO::getInstance().getByPhoneNum(userId)) {
			User rr = std::move(*r);
			delete r;
			return rr;
		}
		return std::nullopt;
	}
	
	// [Method] Get user by card number
	std::optional<User> GetUserByPhoneNum(const std::string& phoneNum)
	{
		if (User* r = UserDAO::getInstance().getByPhoneNum(userId)) {
			User rr = std::move(*r);
			delete r;
			return rr;
		}
		return std::nullopt;
	}

	// [Method] Get user's cards
	std::optional<std::vector<Card>> GetUserCards(const size_t userId) {
		if (auto userCardsIds = UserDAO::getInstance().getUserCards(userId)) {
			const CardDAO& cardDao = CardDAO::getInstance();
			std::vector<Card> userCards;
			for (const auto& cardId : *userCardsIds) {
				if (Card* card = cardDao.getById(cardId)) {
					userCards.emplace_back(std::move(*card));
					delete card;
				} else {
					return std::nullopt;
				}
			}
			delete userCardsIds;
			return userCards;
		}
		return std::nullopt;
	}

	// [Method] Add card for user
	void AddCardForUser(const Card& card) {
		CardDAO::getInstance().saveCard();
	}
	/*
    void saveCard(Card&) const;

    Card* getById(const QString& id) const;

    std::size_t getBalance(const QString& id) const;

    bool updateCard(const Card&) const;

    void deleteById(const QString& id) const;
	*/
	

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