#include "withdrawscreen.h"
#include "Events/atmbuttonpressedevent.h"
#include "ui_withdrawscreen.h"
#include "Bank/ATM.h"

WithdrawScreen::WithdrawScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::WithdrawScreen)
{
    ui->setupUi(this);
}

WithdrawScreen::~WithdrawScreen()
{
    delete ui;
}

void WithdrawScreen::onATMButtonPressed(ATMButtonPressedEvent *event) {
    ATMScreen::onATMButtonPressed(event);

    ATMButtonId id = event->getButtonId();
    int withdrawn = 0;
    switch (id) {
        case ATMButtonId::b_enter:
            withdrawn = tryWithdraw();

            if(withdrawn == 0)
            {
                ui->mainLabel->setText("Enter desired amount");
                break;
            }

            init(nullptr);
            if (withdrawn > 0)
            {
                ui->mainLabel->setText("Successful withdraw");
            }
            else
            {
                ui->mainLabel->setText("Couldn't withdraw");
            }
            break;
        case ATMButtonId::b_back:
            sendSwitchScreen(ScreenType::Main);
            break;
        case ATMButtonId::r_4:
            ui->moneyLine->clear();
            ui->moneyLine->setFocus();
            break;
        default:
            if (event->isNumber())
            {
                ui->moneyLine->setCursorPosition(static_cast<int>(ui->moneyLine->text().length()));
                ui->moneyLine->insert(QString::number(static_cast<int>(id)));
            }
    }
}

void WithdrawScreen::init(QObject *initObject) {
    ATMScreen::init(initObject);

    const ATM& atm = ATM::getInstance();
    const Card* card = atm.getInsertedCard();
    ui->mainLabel->setText("Enter desired amount");
    ui->yourBalanceLabel->setText("Your balance: " + QString::number(card->GetBalance()));
    ui->withdrawAmmountLabel->setText("Possible to withdraw: " + QString::number(atm.getAvailableWithdraw()));
    ui->moneyLine->clear();
    ui->moneyLine->setFocus();
}

uint8_t WithdrawScreen::tryWithdraw() const {
    QString text = ui->moneyLine->text();
    uint32_t value = text.toInt();

    if (value <= 0)
    {
        return 0;
    }

    qDebug("Attempt to withdraw %d money", value);
    if (ATM::getInstance().withdrawMoney(value))
    {
        return 1;
    }
    return -1;
}
