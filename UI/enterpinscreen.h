#ifndef ENTERPINSCREEN_H
#define ENTERPINSCREEN_H

#include "atmscreen.h"

namespace Ui {
class EnterPinScreen;
}

class EnterPinScreen : public ATMScreen
{
    Q_OBJECT

public:
    explicit EnterPinScreen(QWidget *parent = nullptr);
    ~EnterPinScreen();

private:
    Ui::EnterPinScreen *ui;
};

#endif // ENTERPINSCREEN_H
