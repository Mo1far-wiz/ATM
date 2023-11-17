#ifndef SWITCHSCREENEVENT_H
#define SWITCHSCREENEVENT_H

#include <QEvent>
#include "screentype.h"

class SwitchScreenEvent : public QEvent
{
public:
    static const QEvent::Type SwitchScreen = static_cast<QEvent::Type>(3000);

    SwitchScreenEvent(ScreenType type, const QObject* initObject = nullptr);

    inline ScreenType getScreenType() const { return _type; }
    inline const QObject* getInitObject() const { return _initObject; }

private:
    ScreenType _type;
    const QObject* _initObject;

};

#endif // SWITCHSCREENEVENT_H
