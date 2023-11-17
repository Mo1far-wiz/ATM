cmake_minimum_required(VERSION 3.5)

project(ATM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/Users/oleksandr/Desktop/naukma/moop/Qt/6.6.0/macos")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6Widgets REQUIRED)
find_package(Qt6Sql REQUIRED)
find_package(Qt6Test REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Bank/ATM.cpp
        Bank/ATM.h
        Bank/Bank.cpp
        Bank/Bank.h
        Bank/Tracsaction.cpp
        Bank/Transaction.h
        Cards/Card.cpp
        Cards/Card.h
        Cards/CardType.h
        Cards/CreditCard.cpp
        Cards/CreditCard.h
        Cards/CVV.h
        Cards/DebitCard.cpp
        Cards/DebitCard.h
        User/User.cpp
        User/User.h
        data_access/CardDAO.cpp data_access/CardDAO.h
        data_access/UserDAO.cpp data_access/UserDAO.h
        data_access/ATM_DAO.cpp data_access/ATM_DAO.h
        data_access/ATM_DAO.cpp data_access/ATM_DAO.h
        data_access/TransactionDAO.cpp data_access/TransactionDAO.h
        data_access/IncludeDataAccess.h
        Events/atmbuttonpressedevent.h Events/atmbuttonpressedevent.cpp
        UI/enterpinscreen.h UI/enterpinscreen.cpp UI/enterpinscreen.ui
        UI/atmscreen.h UI/atmscreen.cpp
        UI/defaultscreen.h UI/defaultscreen.cpp UI/defaultscreen.ui
        Events/switchscreenevent.h Events/switchscreenevent.cpp
        Events/screentype.h
        UI/mainscreen.h UI/mainscreen.cpp UI/mainscreen.ui
        UI/withdrawscreen.h UI/withdrawscreen.cpp UI/withdrawscreen.ui)
        UI/withdrawscreen.h UI/withdrawscreen.cpp UI/withdrawscreen.ui

target_link_libraries(${PROJECT_NAME}
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Sql
        Qt6::Test
        )
