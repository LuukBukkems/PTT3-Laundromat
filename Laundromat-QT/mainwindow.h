#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <serverconnect.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openConnectionWindow();

private slots:
    void on_btnEmStop_clicked();

    void on_btnSelect_clicked();

    void on_btnRefresh_clicked();

    void on_pushButton_clicked();

    void on_btnConnect_clicked();

    void on_btnRemStart_clicked();
    
    void on_btnRemStop_clicked();
    
private:
    Ui::MainWindow *ui;
    Ui::serverConnect *connectionWindow;
};

#endif // MAINWINDOW_H
