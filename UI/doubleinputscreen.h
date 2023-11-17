#ifndef DOUBLEINPUTSCREEN_H
#define DOUBLEINPUTSCREEN_H

#include <QLineEdit>
#include "atmscreen.h"

namespace Ui {
class DoubleInputScreen;
}

class DoubleInputScreen : public ATMScreen
{
    Q_OBJECT

    enum class Mode : uint8_t
    {
        EnterPin,
        Transaction,
    };

public:
    explicit DoubleInputScreen(QWidget *parent = nullptr);
    ~DoubleInputScreen();

    virtual void init(const QObject* initObject) override;

private:
    virtual void onATMButtonPressed(ATMButtonPressedEvent* event) override;

    void onEnterPressed();
    void onBackPressed();

    bool tryLogin() const;

    bool tryTransaction() const;

    QString getBalance() const;

    Mode mode = Mode::EnterPin;

    QString defaultText;

    Ui::DoubleInputScreen *ui;
    QLineEdit* currentLine;
};

#endif // DOUBLEINPUTSCREEN_H
