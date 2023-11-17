#ifndef ENTERPINSCREEN_H
#define ENTERPINSCREEN_H

#include <QLineEdit>
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

    virtual void init(const QObject* initObject) override;

private:
    virtual void onATMButtonPressed(ATMButtonPressedEvent* event) override;

    bool tryLogin() const;

    QString defaultText;

    Ui::EnterPinScreen *ui;
    QLineEdit* currentLine;
};

#endif // ENTERPINSCREEN_H
