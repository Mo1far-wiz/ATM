#pragma once

#include <iostream>
#include <QString>
#include "data_access/UserDAO.h"
#include "Cards/Card.h"
#include <functional>

class Bank;
class Card;
struct CVV;

class ATM : IId {
public:
	ATM(const uint32_t id, const uint32_t& moneyLeft) : _id(id), _insertedCard(nullptr), _moneyLeft(moneyLeft) {
	}
	// ! After class is deleted, ptrs to inserted card are not valid anymore
	~ATM() {
		removeInsertedCard();
	}
    [[nodiscard]] uint32_t GetId() const override {
		return _id;
	}
	/*uint32_t GetBankId() const {
		return _bankId;
	}*/
	[[nodiscard]] uint32_t getAvailableWithdraw() const {
		return _moneyLeft;
	}
	[[nodiscard]] uint32_t getInsertedCardId() const {
		return _insertedCard->GetId();
	}
	bool isCardInserted() {
		return _insertedCard;
	}
	void removeInsertedCard() {
		delete _insertedCard;
		_insertedCard = nullptr;
	}
	const Card* getInsertedCard() const {
		return _insertedCard;
	}
	const User* getInsertedCardOwner(const QString& cardNum) {
		User* user = nullptr;
		if (_insertedCard) {
			user = UserDAO::getInstance().getByCardNum(_insertedCard->GetCardNumber());
		}
		return user;
	}

	// Returns true if card is valid and pin is correct
	bool login(const QString& cardNum, const QString& pin) {
		// Check if card exists && Check if pin is correct
		if (Card* card = CardDAO::getInstance().getByCardNum(cardNum)) {
			if (card->GetPinCode() == pin) {
				removeInsertedCard();
				_insertedCard = card;
				return true;
			}
			delete card;
		}
		return false;
	}

	// True - success, false - no
	bool withdrawMoney(const uint32_t amount) {
		float txComission = amount * _insertedCard->GetTransactionCommission();
		if (_moneyLeft < amount && _insertedCard->GetBalance() < amount + txComission) { return false; }
		_moneyLeft -= amount;
		double totalCost -= txComission + amount;
		_insertedCard->GetBalance() -= totalCost;
		CardDAO::getInstance().UpdateCard(_insertedCard->GetCardType() == CardType::Debit ? static_cast<DebitCard&>(*_insertedCard) : static_cast<CreditCard&>(*_insertedCard));
		// tx
		Transaction tx(0, _insertedCard->getId(), 0, totalCost);
		TransactionDAO::getInstance().addTransaction();
		return true;
	}
	
private:
	// Id of ATM
	const uint32_t _id;
	// Amount of money left to withdraw
	uint32_t _moneyLeft;
	// Currently inserted card
	Card* _insertedCard = nullptr;
};
