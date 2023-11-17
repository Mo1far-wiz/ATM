#ifndef WITHDRAWSCREEN_H
#define WITHDRAWSCREEN_H

#include "atmscreen.h"

namespace Ui {
class WithdrawScreen;
}

class WithdrawScreen : public ATMScreen
{
    Q_OBJECT

public:
    explicit WithdrawScreen(QWidget *parent = nullptr);
    ~WithdrawScreen();

    virtual void init(const QObject* initObject) override;

protected:
    virtual void onATMButtonPressed(ATMButtonPressedEvent* event) override;

private:
    uint8_t tryWithdraw() const;

    Ui::WithdrawScreen *ui;
};

#endif // WITHDRAWSCREEN_H
