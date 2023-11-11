#include "defaultscreen.h"
#include "ui_defaultscreen.h"

DefaultScreen::DefaultScreen(QWidget *parent)
    : ATMScreen(parent)
    , ui(new Ui::DefaultScreen)
{
    ui->setupUi(this);
}

DefaultScreen::~DefaultScreen()
{
    delete ui;
}
