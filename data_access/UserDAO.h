//
// Created by Oleksandr on 05.11.2023.
//

#ifndef ATM_USERDAO_H
#define ATM_USERDAO_H

#include "User/User.h"

class UserDAO {
public:
    static UserDAO& getInstance();

    User* getById(std::size_t id) const;
    User* getByPhoneNum(std::string phoneNum) const;
    User* getByCardNum(std::string cardNumber) const;

    std::vector<std::size_t> getUserCards(std::size_t userId);

private:
    static void initialize();
    UserDAO() = default;
};


#endif //ATM_USERDAO_H
