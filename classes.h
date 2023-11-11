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
class User;
class Card;
class DebitCard;
class Transaction;

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
	std::string ToString() const {
		return "[User]: Id: " + std::to_string(_id) + " Name: " + _name + " Surname: " + _surname + " phone: " + _phoneNum;
	}

private:
	std::string _name;
	std::string _surname;
	std::string _phoneNum;
	const size_t _id;
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
	float GetWithdrawCommission() const {
		return _widthdrawCommission;
	}
	virtual ~Card() {}

	virtual std::string ToString() const {
		return "[Card]: Id: " + std::to_string(_id) + " Number: " + _cardNumber + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv;
	}

protected:
	Card(const size_t id, const std::string& cardNumber, 
		const std::string& cvv, const size_t ownerId, const double currentBalance,
		const size_t expireDate, const CardType cardType, const float transactionCommission,
		const float witdrawCommission, const std::string& pin) 
		: _id(id), _cardNumber(cardNumber), _cvv(cvv), _ownerId(ownerId), _currentBalance(currentBalance),
		_expireDate(expireDate), _cardType(cardType), _transactionCommission(transactionCommission),
		_witdrawCommission(withdrawCommission), _pinCode(pin)
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
	const size_t _id;
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

	virtual std::string ToString() const {
		return "[DebitCard]: Id: " + std::to_string(_id) + " Number: " + _cardNumber + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv;
	}
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
	virtual std::string ToString() const override {
		return "[CreditCard]: Id: " + std::to_string(_id) + " Number: " + _cardNumber + " OwnerId: " + std::to_string(_ownerId) + " cvv: " + _cvv + " creditLimit: " + _creditLimit;
	}
private:
	size_t _creditLimit;
};

class Transaction : IId {
public:
	Transaction(const size_t id, const size_t from, const size_t to, const double amount)
		: _id(id), _from(from), _to(to), _amount(amount)
	{}
	size_t GetId() const override {
		return _id;
	}
	size_t GetFrom() const {
		return _from;
	}
	size_t GetTo() const {
		return _to;
	}
	double GetAmount() const {
		return _amount;
	}

	std::string ToString() const {
		return "[Transaction]: Id: " + std::to_string(_id) + " From: " + std::to_string(_from) + " To: " + std::to_string(_to) + " Amount: " + std::to_string(_amount);
	}
private:
	const size_t _id;
	const size_t _from;
	const size_t _to;
	const double _amount;
};

class ATM : IId {
public:
	ATM(size_t id) : _bankRef(bank), id(id) {

	}
	~ATM() {}
	size_t GetId() const override {
		return _id;
	}
	size_t GetBankId() const {
		return _bankId;
	}
	size_t GetAvailableWithdraw() const {
		return _moneyLeft;
	}
	size_t GetInsertedCardId() const {
		return _insertedCardId;
	}

	std::optional<DebitCard> GetDebitCardByNumber(const QString& num) {
		return 
	}

	// [Method] Insert & Verify card
	void AcceptCard(const Card&);

	// [Method] Create a transaction and make Bank process it
	void CreateTransaction(const Card& from, const Card& to, size_t amount);
	// [Method] Check balance
	size_t GetBalance();
	// [Method] Change CVV
	void ChangeCVV(const CVV oldCvv);
	
private:
	const size_t _id;
	// Bank id
	size_t _bankId;
	// Amount of money left to withdraw
	size_t _moneyLeft;
	// Currently inserted card
	size_t _insertedCardId;

	std::optional<CreditCard> GetCreditCard() {
	return Get<CardDAO, size_t, Card*, CreditCard>(8, &CardDAO::getCard,
		[](Card* r) {
			if (r->GetCardType() == CardType::Credit) {
				CreditCard cr = std::move(*static_cast<CreditCard*>(r));
				delete r;
				return cr;
			}
			throw 0;
		});
	}

	std::optional<DebitCard> GetDebitCard() {
	return Get<CardDAO, size_t, Card*, DebitCard>(8, &CardDAO::getCard, [](Card* r) {
			if (r->GetCardType() == CardType::Debit) {
				DebitCard cr = std::move(*static_cast<DebitCard*>(r));
				delete r;
				return cr;
			}
			throw 0;
		});
	}
	
	/* --- DAO interaction --- */
	/**
	 * Default handler for Get function.
	 * By default, DAO return dynamically allocated ptr, so this handler deletes it so that user of Get doesn't have to
	 */
	template <class R, class U>
	R DefaultGetHandler(U& r) {
		if (r) {
			R rr = std::move(*r);
			delete r;
			return rr;
		}
		throw 0;
	}

	/**
	 * Get R from DAO using its getter method which has U as arg and DaoR as return type
	 * By default, DaoR must be a pointer
	 * @param key param which will be passed to method of DAO
	 * @param getter pointer to method of DAO
	 * @param handler function, which takes DaoR& and returns R, also it can throw to make function Get return std::nullopt
	 * @return Requested object of type R as std::optional<R>, std::nullopt if db query failed, or handler has thrown something
	 */
	template <class DAO, class U, class DaoR, class R>
	std::optional<R> Get(const U& key, DaoR(DAO::* getter)(const U&), R(*f)(DaoR&) = DefaultGetHandler<R, DaoR>) {
		DaoR r = (DAO::getInstance().*getter)(key);
		try {
			return f(r);
		}
		catch (...) {
			return std::nullopt;
		}
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
				}
				else {
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
