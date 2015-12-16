#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timer_elapsed()));
    timer->start(1);//one millisecond
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_timer_elapsed()
{
   // qDebug() << "yes";
}

void MainWindow::on_btnEmStop_clicked()
{
    //SEND STOP TO ALL MACHINES ON THE CONNECTED SERVER
}

void MainWindow::on_btnSelect_clicked()
{
    //Selects (selected on the machine statuses window) and gets all info from server
}

void MainWindow::on_btnRefresh_clicked()
{
    //Gets a new list of connected machines from the server
}


void MainWindow::on_btnRemStart_clicked()
{
    //Pre: A program must be selected OR Machine must not be running
    //Send server message to start machine with selected program
}

void MainWindow::on_btnConnect_clicked()
{
    //Pre: A program must be selected OR Machine must not be running
    //Send server message to start machine with selected program

    openConnectionWindow();
}

void MainWindow::on_btnRemStop_clicked()
{
    //Pre: Machine must be running
    //Send server message to stop machine
}

void MainWindow::openConnectionWindow()
{
    serverConnectWindow connectionwindow;
    connectionwindow.setModal(true);

    connectionwindow.setMainWindowHandle(this);

    connectionwindow.exec();
}

