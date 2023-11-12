#include "enterpinscreen.h"
#include "ui_enterpinscreen.h"

EnterPinScreen::EnterPinScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::EnterPinScreen)
{
    ui->setupUi(this);
}

EnterPinScreen::~EnterPinScreen()
{
    delete ui;
}
