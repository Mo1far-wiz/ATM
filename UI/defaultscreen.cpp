#include "defaultscreen.h"
#include "ui_defaultscreen.h"
#include "Events/atmbuttonpressedevent.h"

DefaultScreen::DefaultScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::DefaultScreen)
{
    ui->setupUi(this);
}

DefaultScreen::~DefaultScreen()
{
    delete ui;
}

void DefaultScreen::onATMButtonPressed(ATMButtonPressedEvent *event) {
    ATMScreen::onATMButtonPressed(event);

    if (event->getButtonId() == ATMButtonId::b_enter)
    {
        sendSwitchScreen(ScreenType::EnterPin);
    }
}
