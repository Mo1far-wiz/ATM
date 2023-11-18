#include "infoscreen.h"
#include "ui_infoscreen.h"
#include "Events/atmbuttonpressedevent.h"
#include "User/User.h"

InfoScreen::InfoScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::InfoScreen)
{
    ui->setupUi(this);
}

InfoScreen::~InfoScreen()
{
    delete ui;
}

void InfoScreen::init(const QObject *initObject) {
    ATMScreen::init(initObject);

    ui->infoList->clear();
    if (const User* user = dynamic_cast<const User*>(initObject))
    {
        ui->mainLabel->setText("User info");
        ui->mainInfo->setText(user->GetName() + " " + user->GetSurname());
        ui->optionalInfo->setText(user->GetPhoneNumber());
        const QList<std::shared_ptr<Card>>& cards = user->getUserCards();
        for (const std::shared_ptr<Card>& card : cards)
        {
            ui->infoList->addItem(card->ToString());
        }
        return;
    }
    if (const Card* card = dynamic_cast<const Card*>(initObject))
    {
        ui->mainLabel->setText("Card info");
        ui->mainInfo->setText(card->GetCardNumber());
        ui->optionalInfo->setText("");
        const QList<std::shared_ptr<Transaction>>& transactions = card->GetAllTransactions();
        for (const std::shared_ptr<Transaction>& transaction : transactions)
        {
            ui->infoList->addItem(transaction->ToString());
        }
        return;
    }
}

void InfoScreen::onATMButtonPressed(ATMButtonPressedEvent *event) {
    ATMScreen::onATMButtonPressed(event);

    if (event->getButtonId() == ATMButtonId::b_back)
    {
        sendSwitchScreen(ScreenType::Main);
    }
}
