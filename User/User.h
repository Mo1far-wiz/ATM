#include <iostream>
#include <vector>

class Card;

class User {
    size_t id;
    std::vector<Card*> cards;
    std::string name;
    std::string surname;
};
