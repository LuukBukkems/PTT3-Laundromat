#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serverconnectwindow.h>
#include <QTimer>
#include <QDebug>
#include "RigidSpectreNETConnector.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;

public slots:
    void openConnectionWindow();
    void on_timer_elapsed();

private slots:
    void on_btnEmStop_clicked();

    void on_btnSelect_clicked();

    void on_btnRefresh_clicked();

    void on_btnConnect_clicked();

    void on_btnRemStart_clicked();
    
    void on_btnRemStop_clicked();

};

#endif // MAINWINDOW_H
