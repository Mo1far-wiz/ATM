#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "Events/atmbuttonpressedevent.h"
#include "Bank/ATM.h"

MainScreen::MainScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::MainScreen)
{
    ui->setupUi(this);
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::onATMButtonPressed(ATMButtonPressedEvent *event) {
    ATMScreen::onATMButtonPressed(event);

    ATMButtonId id = event->getButtonId();

    switch (id)
    {
        case ATMButtonId::l_3:
            sendSwitchScreen(ScreenType::Withdraw);
            break;
        case ATMButtonId::l_4:
            sendSwitchScreen(ScreenType::DoubleInput, ATM::getInstance().getInsertedCard());
            break;
        case ATMButtonId::r_3:
            sendSwitchScreen(ScreenType::Info, ATM::getInstance().getInsertedCardOwner().get());
            break;
        case ATMButtonId::r_4:
            sendSwitchScreen(ScreenType::Info, ATM::getInstance().getInsertedCard());
            break;
        case ATMButtonId::b_back:
            sendSwitchScreen(ScreenType::Default);
            break;
        default:
            break;
    }
}

void MainScreen::init(const QObject *initObject) {
    ATMScreen::init(initObject);

    QString name = ATM::getInstance().getInsertedCardOwner()->GetName();
    ui->nameLabel->setText("Welcome, " + name);
}
