#ifndef ATMBUTTONPRESSEDEVENT_H
#define ATMBUTTONPRESSEDEVENT_H

#include <QEvent>

enum class ATMButtonId : int
{
    b_0 = 0, b_1, b_2, b_3, b_4, b_5, b_6, b_7, b_8, b_9, b_back, b_enter,
    l_1, l_2, l_3, l_4, r_1, r_2, r_3, r_4,
};

class ATMButtonPressedEvent : public QEvent
{
public:
    static const QEvent::Type ATMButtonPressed = static_cast<QEvent::Type>(2000);

    ATMButtonPressedEvent(ATMButtonId id);

    inline ATMButtonId getButtonId() const { return _id; }

    inline bool isNumber() const { return _id >= ATMButtonId::b_0 && _id <= ATMButtonId::b_9; }

private:
    ATMButtonId _id;

};

#endif // ATMBUTTONPRESSEDEVENT_H
