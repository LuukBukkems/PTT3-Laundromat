#ifndef SERVERCONNECTWINDOW_H
#define SERVERCONNECTWINDOW_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class serverConnectWindow;
}

class MainWindow;

class serverConnectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit serverConnectWindow(QWidget *parent = 0);
    ~serverConnectWindow();

    void setMainWindowHandle(MainWindow* h);

private slots:
    void on_AcceptConnect_accepted();

    void on_AcceptConnect_rejected();

private:
    Ui::serverConnectWindow *ui;
    MainWindow* windowh;
};

#endif // SERVERCONNECTWINDOW_H
