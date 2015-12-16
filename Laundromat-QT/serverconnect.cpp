#include "serverconnect.h"
#include "ui_serverconnect.h"

serverConnect::serverConnect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverConnect)
{
    ui->setupUi(this);
}

serverConnect::~serverConnect()
{
    delete ui;
}
