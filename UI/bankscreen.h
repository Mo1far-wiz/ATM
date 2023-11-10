#ifndef BANKSCREEN_H
#define BANKSCREEN_H

#include <QWidget>

namespace Ui {
class BankScreen;
}

class ATMButtonPressedEvent;

class BankScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BankScreen(QWidget *parent = nullptr);
    ~BankScreen();

    virtual bool event(QEvent* event) override;

private:
    void onATMButtonPressed(ATMButtonPressedEvent* event);

    Ui::BankScreen *ui;
};

#endif // BANKSCREEN_H
