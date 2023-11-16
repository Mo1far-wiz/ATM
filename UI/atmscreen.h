#ifndef ATMSCREEN_H
#define ATMSCREEN_H

#include <QWidget>
#include "Events/screentype.h"

class ATMButtonPressedEvent;

class ATMScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ATMScreen(QWidget *parent = nullptr);

    virtual bool event(QEvent* event) override;

    virtual void init(QObject* initObject);

protected:
    virtual void onATMButtonPressed(ATMButtonPressedEvent* event);

    void sendSwitchScreen(ScreenType type) const;

signals:
};

#endif // ATMSCREEN_H
