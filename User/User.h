#include <iostream>
#include <vector>

class Card;

struct User {
    User(const uint32_t id, const std::string name, const std::string surname, const std::string phoneNum)
            : id(id), name(name), surname(surname), phoneNum(phoneNum) {

    }
    ~User() {}
    uint32_t id;
    std::string name;
    std::string surname;
    std::string phoneNum;
    std::vector<size_t> cards;

    std::string toString() const {
        std::string result;

        result += "ID: " + std::to_string(id) + "\n";
        result += "Name: " + name + "\n";
        result += "Surname: " + surname + "\n";
        result += "Phone Number: " + phoneNum + "\n";
        result += "Cards: ";

        for (const size_t& card : cards) {
            result += std::to_string(card) + " ";
        }
        result += "\n";

        return result;
    }


};

