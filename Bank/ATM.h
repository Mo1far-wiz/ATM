#include <iostream>
#include <QString>
#include "data_access/CardDAO.h"
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
		RemoveInsertedCard();
	}
	[[nodiscard]] uint32_t GetId() const override {
		return _id;
	}
	/*uint32_t GetBankId() const {
		return _bankId;
	}*/
	[[nodiscard]] uint32_t GetAvailableWithdraw() const {
		return _moneyLeft;
	}
	[[nodiscard]] uint32_t GetInsertedCardId() const {
		return _insertedCard->GetId();
	}
	bool IsCardInserted() {
		return _insertedCard;
	}
	void RemoveInsertedCard() {
			delete _insertedCard;
	}
	const Card* GetInsertedCard() const {
		return _insertedCard;
	}
	const User* getInsertedCardOwner(const QString& cardNum) {
		User* user = nullptr;
		if (_insertedCard) {
			user = CardDAO::getInstance().getByCardNum(_insertedCard->GetCardNumber());
		}
		return user;
	}

	// Returns true if card is valid and pin is correct
	bool login(const QString& cardNum, const QString& pin) {
		// Check if card exists && Check if pin is correct
		if (Card* card = CardDAO::getInstance().getByCardNum(cardNum)) {
			if (card->GetPinCode() == pin) {
				RemoveInsertedCard();
				_insertedCard = c;
				return true;
			}
			delete card;
		}
		return false;
	}
	
private:
	// Id of ATM
	const uint32_t _id;
	// Amount of money left to withdraw
	uint32_t _moneyLeft;
	// Currently inserted card
	Card* _insertedCard = nullptr;

private:
	
};
