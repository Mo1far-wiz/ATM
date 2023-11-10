#include "bankscreen.h"
#include "Events/atmbuttonpressedevent.h"
#include "ui_bankscreen.h"

BankScreen::BankScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BankScreen)
{
    ui->setupUi(this);
}

BankScreen::~BankScreen()
{
    delete ui;
}

bool BankScreen::event(QEvent* event)
{
    if (event->type() == ATMButtonPressedEvent::ATMButtonPressed)
    {
        onATMButtonPressed(static_cast<ATMButtonPressedEvent*>(event));
        return true;
    }

    return false;
}

void BankScreen::onATMButtonPressed(ATMButtonPressedEvent* event)
{
    qDebug("Button pressed %d", static_cast<int>(event->getButtonId()));
}
