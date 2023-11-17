#include <QtCore/qcoreapplication.h>
#include "atmscreen.h"
#include "Events/atmbuttonpressedevent.h"
#include "Events/switchscreenevent.h"

ATMScreen::ATMScreen(QWidget *parent)
    : QWidget{parent}
{}

bool ATMScreen::event(QEvent *event) {
    if (event->type() == ATMButtonPressedEvent::ATMButtonPressed)
    {
        onATMButtonPressed(static_cast<ATMButtonPressedEvent*>(event));
        return true;
    }

    return QWidget::event(event);
}

void ATMScreen::onATMButtonPressed(ATMButtonPressedEvent *event) {
    qDebug("Button pressed %d, caught by %s", static_cast<int>(event->getButtonId()), qUtf8Printable(objectName()));
}

void ATMScreen::sendSwitchScreen(ScreenType type, const QObject* initObject) const {
    SwitchScreenEvent event(type, initObject);
    QCoreApplication::sendEvent(window(), &event);
}

void ATMScreen::init(const QObject* initObject) {
    qDebug("%s init", qUtf8Printable(objectName()));
}
