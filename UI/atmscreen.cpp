#include "atmscreen.h"
#include "Events/atmbuttonpressedevent.h"

ATMScreen::ATMScreen(QWidget *parent)
    : QWidget{parent}
{}

bool ATMScreen::event(QEvent *event) {
    if (event->type() == ATMButtonPressedEvent::ATMButtonPressed)
    {
        onATMButtonPressed(static_cast<ATMButtonPressedEvent*>(event));
        return true;
    }

    return false;
}

void ATMScreen::onATMButtonPressed(ATMButtonPressedEvent *event) {
    qDebug("Button pressed %d, caught %s", static_cast<int>(event->getButtonId()), qUtf8Printable(objectName()));

}
