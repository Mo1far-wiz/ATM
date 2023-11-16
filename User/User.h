#include <iostream>
#include <vector>
#include <QString>
#include <QtCore/QObject>

#include "Cards/Card.h"

class User : IId {
public:
	User() {
		std::cout << "User default ctor()\n";
	}
	User(const uint32_t id, const QString& name, const QString& surname)
		: id(id), name(name), surname(surname) {
		std::cout << "User normal ctor()\n";
	}
	~User() {}

	uint32_t GetId() const override {
		return _id;
	}
	const QString& GetName() const {
		return _name;
	}
	const QString& GetSurname() const {
		return _surname;
	}
	const QString& GetPhoneNumber() const {
		return _surname;
	}
	QString ToString() const {
		return (("[User]: Id: " + std::to_string(_id) + " Name: " + _name + " Surname: " + _surname + " phone: " + _phoneNum).c_str());
	}

private:
	QString _name;
	QString _surname;
	QString _phoneNum;
	const uint32_t _id;
};

