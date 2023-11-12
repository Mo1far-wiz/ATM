#include "mainscreen.h"
#include "ui_mainscreen.h"
#include "Events/atmbuttonpressedevent.h"

MainScreen::MainScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::MainScreen)
{
    ui->setupUi(this);
}

MainScreen::~MainScreen()
{
    delete ui;
}

void MainScreen::onATMButtonPressed(ATMButtonPressedEvent *event) {
    ATMScreen::onATMButtonPressed(event);

    ATMButtonId id = event->getButtonId();

    switch (id)
    {
        case ATMButtonId::l_3:
            break;
        case ATMButtonId::l_4:
            break;
        case ATMButtonId::r_3:
            break;
        case ATMButtonId::r_4:
            break;
        case ATMButtonId::b_back:
            sendSwitchScreen(ScreenType::Default);
            break;
        default:
            break;
    }
}

void MainScreen::init(QObject *initObject) {
    ATMScreen::init(initObject);

    // cast init obj to user and set name
}
