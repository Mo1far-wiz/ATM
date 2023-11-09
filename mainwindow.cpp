#include "mainwindow.h"
#include <QSignalMapper>
#include "Events/atmbuttonpressedevent.h"
#include "./ui_mainwindow.h"

#define BIND_BUTTON(button) \
    connect(ui->button, SIGNAL(clicked()), signalMapper, SLOT(map())); \
    signalMapper->setMapping(ui->button, static_cast<int>(ATMButtonId::button))


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , signalMapper(new QSignalMapper(this))
{
    ui->setupUi(this);

    BIND_BUTTON(b_0);
    BIND_BUTTON(b_1);
    BIND_BUTTON(b_2);
    BIND_BUTTON(b_3);
    BIND_BUTTON(b_4);
    BIND_BUTTON(b_5);
    BIND_BUTTON(b_6);
    BIND_BUTTON(b_7);
    BIND_BUTTON(b_8);
    BIND_BUTTON(b_9);
    BIND_BUTTON(b_back);
    BIND_BUTTON(b_enter);
    BIND_BUTTON(l_1);
    BIND_BUTTON(l_2);
    BIND_BUTTON(l_3);
    BIND_BUTTON(l_4);
    BIND_BUTTON(r_1);
    BIND_BUTTON(r_2);
    BIND_BUTTON(r_3);
    BIND_BUTTON(r_4);

    connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(buttonClick(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete signalMapper;
}

void MainWindow::buttonClick(int id)
{
    ATMButtonPressedEvent event(static_cast<ATMButtonId>(id));
    QCoreApplication::sendEvent(ui->bankScreen, &event);
}

