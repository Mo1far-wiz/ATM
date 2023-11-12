#ifndef ATMSCREEN_H
#define ATMSCREEN_H

#include <QWidget>

class ATMButtonPressedEvent;

class ATMScreen : public QWidget
{
    Q_OBJECT
public:
    explicit ATMScreen(QWidget *parent = nullptr);

    virtual bool event(QEvent* event) override;

private:
    virtual void onATMButtonPressed(ATMButtonPressedEvent* event);

signals:
};

#endif // ATMSCREEN_H
