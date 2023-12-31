#include "enterpinscreen.h"
#include "ui_enterpinscreen.h"
#include "Events/atmbuttonpressedevent.h"
#include "Bank/ATM.h"

EnterPinScreen::EnterPinScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::EnterPinScreen)
{
    ui->setupUi(this);
    defaultText = ui->label->text();
}

EnterPinScreen::~EnterPinScreen()
{
    delete ui;
}

void EnterPinScreen::onATMButtonPressed(ATMButtonPressedEvent *event)
{
    ATMScreen::onATMButtonPressed(event);

    ATMButtonId id = event->getButtonId();

    ui->label->setText(defaultText);
    
    switch (id) {
        case ATMButtonId::b_back:
            sendSwitchScreen(ScreenType::Default);
            break;

        case ATMButtonId::b_enter:
            if (tryLogin())
            {
                sendSwitchScreen(ScreenType::Main);
            }
            else
            {
                ui->label->setText("Login failed!");
            }
            break;

        case ATMButtonId::r_3:
            ui->cardNumber->clear();

        case ATMButtonId::l_3:
            currentLine = ui->cardNumber;
            currentLine->setFocus();
            break;

        case ATMButtonId::r_4:
            ui->cardPin->clear();

        case ATMButtonId::l_4:
            currentLine = ui->cardPin;
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

bool EnterPinScreen::tryLogin() const {
    QString num = ui->cardNumber->text();
    QString pin = ui->cardPin->text();
    qDebug("Login attempt. Card %s, PIN %s", qUtf8Printable(num), qUtf8Printable(pin));
    return ATM::getInstance().insertCard(num, pin);
}

void EnterPinScreen::init(const QObject* initObject) {
    ATMScreen::init(initObject);

    ui->cardNumber->clear();
    ui->cardPin->clear();
    ui->label->setText(defaultText);
    currentLine = ui->cardNumber;
    currentLine->setFocus();
}
