#include "atmbuttonpressedevent.h"

ATMButtonPressedEvent::ATMButtonPressedEvent(ATMButtonId id)
    : QEvent(ATMButtonPressed), _id(id)
{
}
