#ifndef INFOSCREEN_H
#define INFOSCREEN_H

#include "atmscreen.h"

namespace Ui {
class InfoScreen;
}

class InfoScreen : public ATMScreen
{
    Q_OBJECT

public:
    explicit InfoScreen(QWidget *parent = nullptr);
    ~InfoScreen();

    virtual void init(const QObject* initObject) override;

protected:
    virtual void onATMButtonPressed(ATMButtonPressedEvent* event) override;

private:
    Ui::InfoScreen *ui;
};

#endif // INFOSCREEN_H
