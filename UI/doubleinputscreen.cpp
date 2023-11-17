#include "doubleinputscreen.h"
#include "ui_doubleinputscreen.h"
#include "Events/atmbuttonpressedevent.h"
#include "Bank/ATM.h"

DoubleInputScreen::DoubleInputScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::DoubleInputScreen)
{
    ui->setupUi(this);
    defaultText = ui->label->text();
}

DoubleInputScreen::~DoubleInputScreen()
{
    delete ui;
}

void DoubleInputScreen::init(const QObject* initObject) {
    ATMScreen::init(initObject);

    if (const Card* card = dynamic_cast<const Card*>(initObject))
    {
        defaultText = "Enter the receiver and amount";
        mode = Mode::Transaction;
        ui->value->setInputMask("999999");
    }
    else
    {
        defaultText = "Please, enter your pin";
        mode = Mode::EnterPin;
        ui->value->setInputMask("9999");
    }
    ui->cardNumber->clear();
    ui->value->clear();
    ui->label->setText(defaultText);
    currentLine = ui->cardNumber;
    currentLine->setFocus();
}

void DoubleInputScreen::onATMButtonPressed(ATMButtonPressedEvent *event)
{
    ATMScreen::onATMButtonPressed(event);

    ATMButtonId id = event->getButtonId();

    ui->label->setText(defaultText);
    
    switch (id) {
        case ATMButtonId::b_back:
            onBackPressed();
            break;

        case ATMButtonId::b_enter:
            onEnterPressed();
            break;

        case ATMButtonId::r_3:
            ui->cardNumber->clear();

        case ATMButtonId::l_3:
            currentLine = ui->cardNumber;
            currentLine->setFocus();
            break;

        case ATMButtonId::r_4:
            ui->value->clear();

        case ATMButtonId::l_4:
            currentLine = ui->value;
            currentLine->setFocus();
            break;

        default:
            if (currentLine && event->isNumber())
            {
                currentLine->setCursorPosition(static_cast<int>(currentLine->text().length()));
                currentLine->insert(QString::number(static_cast<int>(id)));
                break;
            }
    }
}

void DoubleInputScreen::onEnterPressed() {
    switch (mode) {
        case Mode::EnterPin:
            if (tryLogin())
            {
                sendSwitchScreen(ScreenType::Main);
            }
            else
            {
                ui->label->setText("Login failed!");
            }
            break;

        case Mode::Transaction:
            if (tryTransaction())
            {
                ui->label->setText("Transaction successful!");
            }
            else
            {
                ui->label->setText("Transaction failed!");
            }
            break;
    }
}

void DoubleInputScreen::onBackPressed() {
    switch (mode) {
        case Mode::EnterPin:
            sendSwitchScreen(ScreenType::Default);
            break;

        case Mode::Transaction:
            sendSwitchScreen(ScreenType::Main);
            break;

    }
}

bool DoubleInputScreen::tryLogin() const {
    QString num = ui->cardNumber->text();
    QString pin = ui->value->text();
    qDebug("Login attempt. Card %s, PIN %s", qUtf8Printable(num), qUtf8Printable(pin));
    return ATM::getInstance().login(num, pin);
}

bool DoubleInputScreen::tryTransaction() const {
    QString num = ui->cardNumber->text();
    QString val = ui->value->text();
    qDebug("Transaction attempt. Card from %s, Card to %s, val %s", qUtf8Printable(ATM::getInstance().getInsertedCard()->GetCardNumber()), qUtf8Printable(num), qUtf8Printable(val));
    return ATM::getInstance().login(num, val);
}