cmake_minimum_required(VERSION 3.23)
project(ATM)

set(CMAKE_CXX_STANDARD 23)

add_executable(ATM main.cpp Bank.cpp Bank.h ATM.cpp ATM.h User.cpp User.h CardType.cpp Cards/CardType.h Cards/Card.cpp Cards/Card.h Cards/CVV.h Cards/DebitCard.cpp Cards/DebitCard.h Cards/CreditCard.cpp Cards/CreditCard.h Tracsaction.cpp Tracsaction.h)
