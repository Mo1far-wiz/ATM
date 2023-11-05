#include <iostream>
#include <vector>

class Card;

struct User {
    User(const size_t id, const std::string name, const std::string surname)
            : id(id), name(name), surname(surname) {

    }
    ~User() {}
    size_t id;
    std::string name;
    std::string surname;
    std::string phoneNum;
    std::vector<size_t> cards;
};
