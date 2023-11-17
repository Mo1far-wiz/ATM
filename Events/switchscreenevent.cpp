#include "switchscreenevent.h"

SwitchScreenEvent::SwitchScreenEvent(ScreenType type, const QObject* initObject)
    : QEvent(SwitchScreen)
    , _type(type)
    , _initObject(initObject)
{
}
