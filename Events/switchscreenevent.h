#ifndef SWITCHSCREENEVENT_H
#define SWITCHSCREENEVENT_H

#include <QEvent>
#include "screentype.h"

class SwitchScreenEvent : public QEvent
{
public:
    static const QEvent::Type SwitchScreen = static_cast<QEvent::Type>(3000);

    SwitchScreenEvent(ScreenType type);

    inline ScreenType getScreenType() const { return _type; }

private:
    ScreenType _type;

};

#endif // SWITCHSCREENEVENT_H
