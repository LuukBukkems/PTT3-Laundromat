#ifndef SERVERCONNECT_H
#define SERVERCONNECT_H

#include <QDialog>

namespace Ui {
class serverConnect;
}

class serverConnect : public QDialog
{
    Q_OBJECT

public:
    explicit serverConnect(QWidget *parent = 0);
    ~serverConnect();

private:
    Ui::serverConnect *ui;
};

#endif // SERVERCONNECT_H
