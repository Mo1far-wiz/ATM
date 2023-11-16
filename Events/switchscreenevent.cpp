#include "switchscreenevent.h"

SwitchScreenEvent::SwitchScreenEvent(ScreenType type)
    : QEvent(SwitchScreen)
    , _type(type)
{
}
