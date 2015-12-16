#include "serverconnectwindow.h"
#include "ui_serverconnectwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

serverConnectWindow::serverConnectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverConnectWindow)
{
    ui->setupUi(this);
}

serverConnectWindow::~serverConnectWindow()
{
    delete ui;
}

void serverConnectWindow::setMainWindowHandle(MainWindow* h)
{
    windowh = h;
}

void serverConnectWindow::on_AcceptConnect_accepted()
{
    qDebug() << windowh->ui->btnConnect->objectName();
    this->close();
}

void serverConnectWindow::on_AcceptConnect_rejected()
{
    this->close();
}
