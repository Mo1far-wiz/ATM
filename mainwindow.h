#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SwitchScreenEvent;
class QSignalMapper;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual bool event(QEvent* event) override;

private slots:
    void buttonClick(int id);

private:
    void onSwitchScreenEvent(SwitchScreenEvent* event);

    Ui::MainWindow *ui;

    QSignalMapper* signalMapper;

};
#endif // MAINWINDOW_H
