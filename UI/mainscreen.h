#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include "atmscreen.h"

namespace Ui {
class MainScreen;
}

class MainScreen : public ATMScreen
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = nullptr);
    ~MainScreen();

    virtual void init(const QObject* initObject) override;

protected:
    virtual void onATMButtonPressed(ATMButtonPressedEvent* event) override;

private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H
