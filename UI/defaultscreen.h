#ifndef DEFAULTSCREEN_H
#define DEFAULTSCREEN_H

#include "atmscreen.h"

namespace Ui {
class DefaultScreen;
}

class DefaultScreen : public ATMScreen
{
    Q_OBJECT

public:
    explicit DefaultScreen(QWidget *parent = nullptr);
    ~DefaultScreen();

private:
    virtual void onATMButtonPressed(ATMButtonPressedEvent* event) override;

    Ui::DefaultScreen *ui;
};

#endif // DEFAULTSCREEN_H
