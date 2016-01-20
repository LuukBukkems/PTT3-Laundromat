#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include "RigidSpectreNETConnector.h"

#include "laundromatmachine.h"

namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow, public FunctionManager
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
    static MainWindow* master;

    void MakeConnection(const QString& address, int number);

    void UpdateInformation(std::string devicename, std::string parameter, int value);

private slots:

    void on_BTNConnect_clicked();

    void on_QUIT_clicked();

    void on_LISTConnectedMachines_currentTextChanged(const QString &currentText);

    void on_BTNstart_clicked();

    void on_BTNstop_clicked();

    void on_btnEmStop_clicked();

private:

    RigidSpectreNETTCPConnector* connector;

    QList<LaundromatMachine*> machines;
    LaundromatMachine* currentMachine;

public slots:

    void read();
    void update();

};

void UpdateInformationBase(std::string devicename, std::string parameter, int value);

#endif // MAINWINDOW_H
