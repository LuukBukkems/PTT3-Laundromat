/********************************************************************************
** Form generated from reading UI file 'serverconnectwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERCONNECTWINDOW_H
#define UI_SERVERCONNECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_serverConnectWindow
{
public:
    QLineEdit *serverAddress;
    QLabel *label;
    QDialogButtonBox *AcceptConnect;

    void setupUi(QDialog *serverConnectWindow)
    {
        if (serverConnectWindow->objectName().isEmpty())
            serverConnectWindow->setObjectName(QStringLiteral("serverConnectWindow"));
        serverConnectWindow->resize(352, 90);
        serverAddress = new QLineEdit(serverConnectWindow);
        serverAddress->setObjectName(QStringLiteral("serverAddress"));
        serverAddress->setGeometry(QRect(0, 20, 341, 27));
        label = new QLabel(serverConnectWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 71, 17));
        AcceptConnect = new QDialogButtonBox(serverConnectWindow);
        AcceptConnect->setObjectName(QStringLiteral("AcceptConnect"));
        AcceptConnect->setGeometry(QRect(0, 50, 341, 32));
        AcceptConnect->setOrientation(Qt::Horizontal);
        AcceptConnect->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        AcceptConnect->setCenterButtons(false);

        retranslateUi(serverConnectWindow);

        QMetaObject::connectSlotsByName(serverConnectWindow);
    } // setupUi

    void retranslateUi(QDialog *serverConnectWindow)
    {
        serverConnectWindow->setWindowTitle(QApplication::translate("serverConnectWindow", "Dialog", 0));
        label->setText(QApplication::translate("serverConnectWindow", "Server IP:", 0));
    } // retranslateUi

};

namespace Ui {
    class serverConnectWindow: public Ui_serverConnectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERCONNECTWINDOW_H
