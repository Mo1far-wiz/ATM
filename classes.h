#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>
#include <algorithm>
#include "data_access/IncludeDataAccess.h"

class Bank;
class ATM;
struct User;
struct Card;
struct DebitCard;
struct Transaction;

// [Interface] Require type to have an id
struct IId {
	virtual size_t GetId() const = 0;
};

class User : IId {
public:
	using DAO = UserDAO;
	User() {
		std::cout << "User default ctor()\n";
	}
	User(const size_t id, const std::string name, const std::string surname)
		: id(id), name(name), surname(surname) {
		std::cout << "User normal ctor()\n";
	}
	~User() {}

	size_t GetId() const override {
		return _id;
	}
	const std::string& GetName() const {
		return _name;
	}
	const std::string& GetSurname() const {
		return _surname;
	}
	const std::string& GetPhoneNumber() const {
		return _surname;
	}

private:
	std::string _name;
	std::string _surname;
	std::string _phoneNum;
	size_t _id;
	//std::vector<size_t> cards;
};

enum class CardType {
	Debit, Credit
};

class Card : IId {
public:
	using DAO = CardDAO;
	size_t GetId() const override {
		return _id;
	}
	std::string GetCardNumber() const {
		return _cardNumber;
	}
	double GetCurrentBalance() const {
		return _currentBalance;
	}
	const std::string& GetCVV() const {
		return _cvv;
	}
	const std::string& GetPinCode() const {
		return _pinCode;
	}
	size_t GetExpireDate() const {
		return _expireDate;
	}
	CardType GetCardType() const {
		return _cardType;
	}
	size_t GetOwnerId() const {
		return _ownerId;
	}
	float GetTransactionCommission() const {
		return _transactionCommission;
	}
	float GetWidthdrawCommission() const {
		return _widthdrawCommission;
	}
	virtual ~Card() {}

protected:
	Card(const size_t id, const std::string& cardNumber, 
		const std::string& cvv, const size_t ownerId, const double currentBalance,
		const size_t expireDate, const CardType cardType, const float transactionCommission,
		const float witdrawCommission, const std::string& pin) 
		: _id(id), _cardNumber(cardNumber), _cvv(cvv), _ownerId(ownerId), _currentBalance(currentBalance),
		_expireDate(expireDate), _cardType(cardType), _transactionCommission(transactionCommission),
		_witdrawCommission(witdrawCommission), _pinCode(pin)
	{}

private:
	std::string _cardNumber;
	std::string _cvv;
	std::string _pinCode;
	double _currentBalance;
	float _transactionCommission;
	float _widthdrawCommission;
	size_t _expireDate;
	size_t _ownerId;
	size_t _id;
	CardType _cardType;
};

class DebitCard : public Card {
public:
	DebitCard(const size_t id, const std::string& cardNumber,
		const std::string& cvv, const size_t ownerId, const double currentBalance,
		const size_t expireDate, const float transactionCommission,
		const float witdrawCommission, const size_t creditLimit, const std::string& pin)
		: Card(id, cardNumber, cvv, ownerId, currentBalance, expireDate, CardType::Debit, transactionCommission, witdrawCommission, pin)
	{}
};

class CreditCard : public Card {
public:
	CreditCard(const size_t id, const std::string& cardNumber,
		const std::string& cvv, const size_t ownerId, const double currentBalance,
		const size_t expireDate, const float transactionCommission,
		const float witdrawCommission, const size_t creditLimit, const std::string& pin)
		: Card(id, cardNumber, cvv, ownerId, currentBalance, expireDate, CardType::Credit, transactionCommission, witdrawCommission, pin),
		_creditLimit(creditLimit)
	{}

	size_t GetCreditLimit() const {
		return _creditLimit;
	}
private:
	size_t _creditLimit;
};

struct Transaction : IId {
	size_t GetId() const override {
		return _id;
	}
	const size_t from;
	const size_t to;
	const size_t amount;
};


class ATM : IId {
public:
	ATM(Bank& bank, size_t id) : _bankRef(bank), id(id) {

	}
	~ATM() {}
	size_t GetId() const override {
		return _id;
	}
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
	size_t _id;
};

class Bank {
	// [Method] Process transaction
	void ProcessTransaction(const Transaction& t) {

	}

	/* --- ATM --- */
	ATM atm = ATM(*this, 0);

	/* --- Users --- */
	/**
	* Get R from DAO of T using key U
	* @param param which will be passed to DAO of T
	* @paraam
	* @return requested object of type R as std::optional<R>, std::nullopt if db query failed
	*/
	template <class T, class U, class R = T>
	std::optional<R> Get(const U& key, R* (T::DAO::* f)(const U&)) {
		if (R* r = (T::DAO::getInstance().*f)(key)) {
			R rr = std::move(*r);
			delete r;
			return rr;
		}
		return std::nullopt;
	}

	// [Method] Get something by id
	template <class T>
	std::optional<T> GetById(const size_t id) {
		if (T* r = T::DAO::getInstance().getById(id)) {
			T rr = std::move(*r);
			delete r;
			return rr;
		}
		return std::nullopt;
	}
	
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
	

	// [Method] Get transactions history by user
	std::vector<Transaction> GetTransactionsHistoryByUser(const size_t userId);

	// [Method] Get transactions history by card
	std::vector<Transaction> GetTransactionsHistoryByCard(const size_t cardId);

	// [Method] Get user balance
	size_t GetUserBalance(const size_t userId);

	// [Method] Get card balance
	size_t GetCardBalance(const size_t cardId);

};