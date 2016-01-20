/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionRefresh_Machines;
    QAction *actionMachine_List;
    QAction *actionSelect_Machine;
    QWidget *centralWidget;
    QTabWidget *tabControls;
    QWidget *tab;
    QLineEdit *serverAddress;
    QLabel *label;
    QSpinBox *PORTnum;
    QPushButton *BTNConnect;
    QWidget *tabLaunOpts;
    QPushButton *btnEmStop;
    QLabel *lblConMach;
    QLabel *lblMachStats;
    QListWidget *LISTConnectedMachines;
    QTextEdit *TXTStates;
    QPushButton *BTNstart;
    QPushButton *BTNstop;
    QRadioButton *RprogramA;
    QRadioButton *RprogramB;
    QRadioButton *RprogramC;
    QPushButton *QUIT;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(656, 460);
        actionRefresh_Machines = new QAction(MainWindow);
        actionRefresh_Machines->setObjectName(QStringLiteral("actionRefresh_Machines"));
        actionMachine_List = new QAction(MainWindow);
        actionMachine_List->setObjectName(QStringLiteral("actionMachine_List"));
        actionSelect_Machine = new QAction(MainWindow);
        actionSelect_Machine->setObjectName(QStringLiteral("actionSelect_Machine"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabControls = new QTabWidget(centralWidget);
        tabControls->setObjectName(QStringLiteral("tabControls"));
        tabControls->setGeometry(QRect(0, 10, 641, 371));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabControls->sizePolicy().hasHeightForWidth());
        tabControls->setSizePolicy(sizePolicy);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        serverAddress = new QLineEdit(tab);
        serverAddress->setObjectName(QStringLiteral("serverAddress"));
        serverAddress->setGeometry(QRect(20, 80, 341, 27));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 60, 71, 17));
        PORTnum = new QSpinBox(tab);
        PORTnum->setObjectName(QStringLiteral("PORTnum"));
        PORTnum->setGeometry(QRect(370, 80, 91, 27));
        PORTnum->setMinimum(1024);
        PORTnum->setMaximum(6500);
        PORTnum->setValue(2345);
        BTNConnect = new QPushButton(tab);
        BTNConnect->setObjectName(QStringLiteral("BTNConnect"));
        BTNConnect->setGeometry(QRect(360, 110, 99, 27));
        tabControls->addTab(tab, QString());
        tabLaunOpts = new QWidget();
        tabLaunOpts->setObjectName(QStringLiteral("tabLaunOpts"));
        btnEmStop = new QPushButton(tabLaunOpts);
        btnEmStop->setObjectName(QStringLiteral("btnEmStop"));
        btnEmStop->setGeometry(QRect(520, 260, 99, 71));
        btnEmStop->setLayoutDirection(Qt::RightToLeft);
        lblConMach = new QLabel(tabLaunOpts);
        lblConMach->setObjectName(QStringLiteral("lblConMach"));
        lblConMach->setGeometry(QRect(10, 10, 161, 21));
        lblConMach->setAlignment(Qt::AlignCenter);
        lblMachStats = new QLabel(tabLaunOpts);
        lblMachStats->setObjectName(QStringLiteral("lblMachStats"));
        lblMachStats->setGeometry(QRect(190, 10, 121, 17));
        LISTConnectedMachines = new QListWidget(tabLaunOpts);
        LISTConnectedMachines->setObjectName(QStringLiteral("LISTConnectedMachines"));
        LISTConnectedMachines->setGeometry(QRect(10, 40, 171, 291));
        TXTStates = new QTextEdit(tabLaunOpts);
        TXTStates->setObjectName(QStringLiteral("TXTStates"));
        TXTStates->setGeometry(QRect(190, 40, 321, 291));
        TXTStates->setReadOnly(true);
        BTNstart = new QPushButton(tabLaunOpts);
        BTNstart->setObjectName(QStringLiteral("BTNstart"));
        BTNstart->setGeometry(QRect(520, 40, 99, 27));
        BTNstop = new QPushButton(tabLaunOpts);
        BTNstop->setObjectName(QStringLiteral("BTNstop"));
        BTNstop->setGeometry(QRect(520, 170, 99, 31));
        RprogramA = new QRadioButton(tabLaunOpts);
        RprogramA->setObjectName(QStringLiteral("RprogramA"));
        RprogramA->setGeometry(QRect(520, 80, 117, 22));
        RprogramA->setChecked(true);
        RprogramB = new QRadioButton(tabLaunOpts);
        RprogramB->setObjectName(QStringLiteral("RprogramB"));
        RprogramB->setGeometry(QRect(520, 110, 117, 22));
        RprogramC = new QRadioButton(tabLaunOpts);
        RprogramC->setObjectName(QStringLiteral("RprogramC"));
        RprogramC->setGeometry(QRect(520, 140, 117, 16));
        tabControls->addTab(tabLaunOpts, QString());
        QUIT = new QPushButton(centralWidget);
        QUIT->setObjectName(QStringLiteral("QUIT"));
        QUIT->setGeometry(QRect(598, 0, 31, 27));
        QUIT->setLayoutDirection(Qt::RightToLeft);
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        tabControls->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionRefresh_Machines->setText(QApplication::translate("MainWindow", "Refresh Machines", 0));
        actionMachine_List->setText(QApplication::translate("MainWindow", "Connect", 0));
        actionSelect_Machine->setText(QApplication::translate("MainWindow", "Select Machine", 0));
        serverAddress->setText(QApplication::translate("MainWindow", "127.0.0.1", 0));
        label->setText(QApplication::translate("MainWindow", "Server IP:", 0));
        BTNConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        tabControls->setTabText(tabControls->indexOf(tab), QApplication::translate("MainWindow", "Connect to Server", 0));
        btnEmStop->setText(QApplication::translate("MainWindow", "EMERGENCY\n"
"STOP", 0));
        lblConMach->setText(QApplication::translate("MainWindow", "Connected machines", 0));
        lblMachStats->setText(QApplication::translate("MainWindow", "Machine Statuses", 0));
        BTNstart->setText(QApplication::translate("MainWindow", "Start", 0));
        BTNstop->setText(QApplication::translate("MainWindow", "Stop", 0));
        RprogramA->setText(QApplication::translate("MainWindow", "Program A", 0));
        RprogramB->setText(QApplication::translate("MainWindow", "Program B", 0));
        RprogramC->setText(QApplication::translate("MainWindow", "Program C", 0));
        tabControls->setTabText(tabControls->indexOf(tabLaunOpts), QApplication::translate("MainWindow", "Laundromat Options", 0));
        QUIT->setText(QApplication::translate("MainWindow", "X", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
