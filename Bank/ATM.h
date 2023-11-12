#include <iostream>

class Bank;
class Card;
struct CVV;

class ATM : IId {
public:
	ATM(const uint32_t id) : _id(id), _insertedCard(nullptr) {
	}
	~ATM() {
		RemoveInsertedCard();
	}
	uint32_t GetId() const override {
		return _id;
	}
	/*uint32_t GetBankId() const {
		return _bankId;
	}*/
	uint32_t GetAvailableWithdraw() const {
		return _moneyLeft;
	}
	uint32_t GetInsertedCardId() const {
		return _insertedCard->GetId();
	}
	const Card* GetInsertedCard() const {
		return _insertedCard;
	}
	bool IsCardInserted() {
		return _insertedCard;
	}

	void RemoveInsertedCard() {
		if (_insertedCard) {
			delete _insertedCard;
		}
	}
	// Returns true if card is valid and pin is correct
	bool InsertCard(const QString& cardNum, const QString& pin) {
		// Check if card exists && Check if pin is correct
		return Get<CardDAO, QString, Card*, Card*>(cardNum, &CardDAO::getByCardNum, 
		[this, &pin](Card&* c) {
			if (c && c->GetPinCode() == pin) {
				RemoveInsertedCard();
				_insertedCard = c;
				return c;
			}
			throw 0;
		});
	}
	
private:
	// Id of ATM
	const uint32_t _id;
	// Amount of money left to withdraw
	uint32_t _moneyLeft;
	// Currently inserted card
	Card* _insertedCard = nullptr;

private:
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
};