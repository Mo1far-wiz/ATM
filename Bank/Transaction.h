#include <iostream>
#include <QString>
#include "IId.h"

class Transaction : IId {
public:
    Transaction(const uint32_t id, const uint32_t from, const uint32_t to, const double amount)
            : _id(id), _from(from), _to(to), _amount(amount)
    {}
    uint32_t GetId() const override {
        return _id;
    }
    uint32_t GetFrom() const {
        return _from;
    }
    uint32_t GetTo() const {
        return _to;
    }
    double GetAmount() const {
        return _amount;
    }
    QString ToString() const {
        return ("[Transaction]: Id: " + std::to_string(_id) + " From: " + std::to_string(_from) + " To: " + std::to_string(_to) + " Amount: " + std::to_string(_amount)).c_str();
    }
private:
    const uint32_t _id;
    const uint32_t _from;
    const uint32_t _to;
    const double _amount;
};