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
<<<<<<< HEAD
=======
	[[nodiscard]] const Card* GetInsertedCard() const {
		return _insertedCard;
	}
>>>>>>> 28f4dbfdba76e2c27bf4de886ffb6af83e03f022
	bool IsCardInserted() {
		return _insertedCard;
	}
	void RemoveInsertedCard() {
<<<<<<< HEAD
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
=======
        delete _insertedCard;
        _insertedCard = nullptr;
    }
	// Returns true if card is valid and pin is correct
	inline bool InsertCard(const QString& cardNum, const QString& pin);
>>>>>>> 28f4dbfdba76e2c27bf4de886ffb6af83e03f022
	
private:
	// Id of ATM
	const uint32_t _id;
	// Amount of money left to withdraw
	uint32_t _moneyLeft;
	// Currently inserted card
	Card* _insertedCard = nullptr;

private:
<<<<<<< HEAD
	
};
=======
	/**
	 * Default handler for Get function.
	 * By default, DAO return dynamically allocated ptr, so this handler deletes it so that user of Get doesn't have to
	 */
	template <class R, class U>
    static R DefaultGetHandler(U& r) {
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
	std::optional<R> Get(const U& key, DaoR(DAO::* getter)(const U&) const, std::function<R(DaoR&)> f = DefaultGetHandler<R, DaoR>
                         //R(*f)(DaoR&) = DefaultGetHandler<R, DaoR>
                                 ) {
		DaoR r = (DAO::getInstance().*getter)(key);
		try {
			return f(r);
		}
		catch (...) {
			return std::nullopt;
		}
	}
};


inline bool ATM::InsertCard(const QString& cardNum, const QString& pin) {
    auto l = [this, &pin](Card*& c) -> Card* {
        if (c && c->GetPinCode() == pin) {
            RemoveInsertedCard();
            _insertedCard = c;
            return c;
        }
        throw 0;
    };
        // Check if card exists && Check if pin is correct
        return (bool)Get<CardDAO, QString, Card*, Card*>(cardNum, &CardDAO::getByCardNum,l);
}
>>>>>>> 28f4dbfdba76e2c27bf4de886ffb6af83e03f022
