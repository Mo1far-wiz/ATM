#pragma once

#include <iostream>
#include <QString>
#include "data_access/UserDAO.h"
#include "Cards/Card.h"
#include "Cards/DebitCard.h"
#include "Cards/CreditCard.h"
#include "data_access/TransactionDAO.h"
#include <functional>

class Bank;
class Card;
struct CVV;

class ATM : IId {
public:
    static ATM& getInstance() {
        static ATM atm(0, 100000);
        return atm;
	}
    [[nodiscard]] uint32_t GetId() const override {
		return _id;
	}
	[[nodiscard]] uint32_t getAvailableWithdraw() const {
		return _moneyLeft;
	}
	[[nodiscard]] uint32_t getInsertedCardId() const {
		return _insertedCard->GetId();
	}
	void removeInsertedCard() {
		delete _insertedCard;
		_insertedCard = nullptr;
	}

	const Card* getInsertedCard() const {
		return _insertedCard;
	}

	const User* getInsertedCardOwner() {
		User* user = nullptr;
		if (_insertedCard) {
			user = UserDAO::getInstance().getByCardNum(_insertedCard->GetCardNumber());
		}
		return user;
	}

	// Returns true if card is valid and pin is correct
	bool insertCard(const QString& cardNum, const QString& pin) {
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

	bool isCardInserted() {
		return _insertedCard;
	}

	// True - success, false - no
	bool withdrawMoney(const uint32_t amount) {
        if(!isCardInserted()) {
            return false;
        }
		float txComission = amount * _insertedCard->GetWithdrawCommission();
		if (_moneyLeft < amount || _insertedCard->GetBalance() < amount + txComission) { return false; }
		_moneyLeft -= amount;
		double totalCost = amount + txComission;
		_insertedCard->GetBalance() -= totalCost;
		updateCard();
        // Add tx
		Transaction tx(0, _insertedCard->GetId(), 0, totalCost);
		TransactionDAO::getInstance().addTransaction(&tx);
		return true;
	}

	bool sendTransaction(const QString& recvCardNum, const uint32_t amount) {
        if(recvCardNum == _insertedCard->GetCardNumber())
        {
            return false;
        }
		// Check if card is inserted
		if (!isCardInserted()) { return false; }
		// Check if card balaance is enough to create transaction
		float txComission = amount * _insertedCard->GetTransactionCommission();
		if (_insertedCard->GetBalance() < amount + txComission) { return false; }
		// Check if recv card exists
		if (Card* recvCard = CardDAO::getInstance().getByCardNum(recvCardNum)) {	
			double totalCost = amount + txComission;
			_insertedCard->GetBalance() -= totalCost;
			updateCard();
			// Add tx
			Transaction tx(0, _insertedCard->GetId(), recvCard->GetId(), amount);
			TransactionDAO::getInstance().addTransaction(&tx);
            recvCard->receiveMoney(amount);
            if(recvCard->GetCardType() == CardType::Debit)
            {
                CardDAO::getInstance().UpdateCard( dynamic_cast<DebitCard&>(*recvCard));
            }
            else if (recvCard->GetCardType() == CardType::Credit)
            {
                CardDAO::getInstance().UpdateCard( dynamic_cast<CreditCard&>(*recvCard));
            }
			delete recvCard;
		    return true;
		}
        return false;
	}

    ~ATM() {
        removeInsertedCard();
    }
private:
    // ! After class is deleted, ptrs to inserted card are not valid anymore
    ATM(const uint32_t id, const uint32_t& moneyLeft) : _id(id), _insertedCard(nullptr), _moneyLeft(moneyLeft) {
    }
	// Update card in DB
	void updateCard() {
		if(_insertedCard->GetCardType() == CardType::Debit) {
            CardDAO::getInstance().UpdateCard(dynamic_cast<DebitCard&>(*_insertedCard));
        }
        else if (_insertedCard->GetCardType() == CardType::Credit) {
            CardDAO::getInstance().UpdateCard(dynamic_cast<CreditCard&>(*_insertedCard));
        }
	}
	// Id of ATM
	const uint32_t _id;
	// Amount of money left to withdraw
	uint32_t _moneyLeft;
	// Currently inserted card
	Card* _insertedCard = nullptr;
};
