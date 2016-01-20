#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtTest/QTest>

MainWindow* MainWindow::master = NULL;

void MainWindow::UpdateInformation(std::string devicename, std::string parameter, int value)
{
    LaundromatMachine* machine = NULL;

    QString deviceName = QString::fromStdString(devicename);

    foreach( LaundromatMachine* item, machines )
    {
        if(item->GetName().compare(deviceName) == 0)
        {
            machine = item;
            break;
        }
    }

    if(machine == NULL) return;

    if(parameter.compare("Speed :")==0)
    {
        machine->SetState(Speed, value);
    }
    else
    if(parameter.compare("Rotation :")==0)
    {
        machine->SetState(Rotation, value);
    }
    else
    if(parameter.compare("Lock :")==0)
    {
        machine->SetState(isLocked, value);
    }
    else
    if(parameter.compare("Sink :")==0)
    {
        machine->SetState(sinkOpen, value);
    }
    else
    if(parameter.compare("Drain :")==0)
    {
        machine->SetState(drainOpen, value);
    }
    else
    if(parameter.compare("Program :")==0)
    {
        machine->SetState(activeProgram, value);
    }
    else
    if(parameter.compare("State :")==0)
    {
        machine->SetState(runningState, value);
    }

}
void Stopped()
{
    qDebug() << "hurr";
}

void UpdateInformationBase(std::string devicename, std::string parameter, int value)
{
   MainWindow::master->UpdateInformation(devicename, parameter, value);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connector(NULL)
{
    master = this;

    ui->setupUi(this);

    currentMachine = NULL;

    AddFunction("UpdateInformation", new Delegate3<void, std::string, std::string, int>(UpdateInformationBase));
    AddFunction("Stopped", new Delegate0<void>(Stopped));

    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        timer->start(700);

    timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(read()));
        timer->start(1);

    LaundromatMachine* m = new LaundromatMachine();

    m->SetName("WashingMachine");
    m->SetConnectionID("dTSws");

    m->SetState(activeProgram, 1);

    machines.push_back(m);
}

void MainWindow::read()
{
    if(connector != NULL && connector->IsStillConnected())
    {
        connector->Read();
    }
}

void MainWindow::update()
{
    if(connector == NULL || !connector->IsStillConnected()) return;


    int curIndex = ui->LISTConnectedMachines->currentRow();

    ui->LISTConnectedMachines->clear();

    CommunicationObject update;
    update.AddDataIndex(new CommunicationObjectType(""));
    update.AddDataIndex(new CommunicationObjectType("GetInformation"));
    update.AddDataIndex(new CommunicationObjectType(""));


    foreach( LaundromatMachine* item, machines )
    {
        update.ReplaceDataIndex(0, new CommunicationObjectType(item->GetConnectionID().toStdString()));

        ui->LISTConnectedMachines->addItem(item->GetName() + " : " + item->GetConnectionID());

        for(int i = 0; i < 7; i++)
        {


            update.ReplaceDataIndex(2, new CommunicationObjectType(i));

            connector->Write(update);
            QTest::qWait(1);

        }
    }

    if(ui->LISTConnectedMachines->count() > curIndex)
    {
       ui->LISTConnectedMachines->setCurrentRow(curIndex);
    }

    if(currentMachine != NULL)
    {
        QString states;

        states += "Running state: ";
        states += (currentMachine->GetState(runningState) > 0) ? "RUNNING" : "IDLE";

        states += "\nActive Program: ";
        states += (currentMachine->GetState(activeProgram) + 64);

        states += "\nLocked: ";
        states += (currentMachine->GetState(isLocked) > 0) ? "TRUE" : "FALSE";
        states += "\ndrainOpen: ";
        states += (currentMachine->GetState(drainOpen) > 0) ? "TRUE" : "FALSE";
        states += "\nsinkOpen: ";
        states += (currentMachine->GetState(sinkOpen) > 0) ? "TRUE" : "FALSE";
        states += "\nSpeed: ";
        states += QString::number(currentMachine->GetState(Speed));
        states += "\nRotation: ";
        states += (currentMachine->GetState(Rotation) > 0) ? "Right" : "Left";

        ui->TXTStates->setText(states);
    }
    else
    {
        ui->TXTStates->setText("Please select a Laundromat machine to see details.");
    }
}

MainWindow::~MainWindow()
{
    delete ui;

    if(connector != NULL)
    {
        connector->SetProcessor(NULL);
        //normally, the connector deletes the functionmanager
        //In this case, the function manager is the mainwindow.
        //To prevent the deletion of an already-being-deleted object, unset processor

        delete connector;
    }
}

void MainWindow::MakeConnection(const QString& address, int number)
{
    if(address.length() > 0)
    {
        connector = new RigidSpectreNETTCPConnector();

        if(connector->Connect(address.toStdString(), number))
        {
            qDebug() << "CONNECTION SUCCESS " +address + ':' + QString::number(number);

            connector->SetProcessor(this);

            connector->IdentifyName("#random");
            connector->IdentifyGroup("#AdministrationLaundromat");
        }
        else
        {
            qDebug() << "CONNECTION FAILED: " +address + ':' + QString::number(number);
        }
    }
}

void MainWindow::on_BTNConnect_clicked()
{
    MakeConnection(ui->serverAddress->text(), ui->PORTnum->value());
}

void MainWindow::on_QUIT_clicked()
{
    QApplication::quit();

}

void MainWindow::on_LISTConnectedMachines_currentTextChanged(const QString &currentText)
{
    QStringList name = currentText.split(":");

    if(name.length() > 1)
    {
        QString conname = name[1];

        conname = conname.trimmed();

        foreach( LaundromatMachine* item, machines )
        {
           if(item->GetConnectionID().compare(conname) == 0)
           {
                currentMachine = item;
                break;
           }
        }
    }
}

void MainWindow::on_BTNstart_clicked()
{
    if(currentMachine != NULL)
    {
       int program = 1;

       if(ui->RprogramA->isChecked())
       {
            program = 1;
       }
       else if(ui->RprogramB->isChecked())
       {
            program = 2;
       }
       else if(ui->RprogramC->isChecked())
       {
            program = 3;
       }


        CommunicationObject startmessage;

        std::string name =currentMachine->GetConnectionID().toStdString();

        startmessage.AddDataIndex(new CommunicationObjectType(name));
        startmessage.AddDataIndex(new CommunicationObjectType("StartProgram"));
        startmessage.AddDataIndex(new CommunicationObjectType(program));


        connector->Write(startmessage);
    }
}

void MainWindow::on_BTNstop_clicked()
{
    if(currentMachine != NULL)
    {
        CommunicationObject stopmessage;

        std::string name = currentMachine->GetConnectionID().toStdString();

        stopmessage.AddDataIndex(new CommunicationObjectType(name));
        stopmessage.AddDataIndex(new CommunicationObjectType("StopProgram"));

        connector->Write(stopmessage);
    }
}

void MainWindow::on_btnEmStop_clicked()
{
    CommunicationObject stopmessage;

    stopmessage.AddDataIndex(new CommunicationObjectType(" "));
    stopmessage.AddDataIndex(new CommunicationObjectType("StopProgram"));

    foreach( LaundromatMachine* item, machines )
    {
        std::string name = item->GetConnectionID().toStdString();

        stopmessage.ReplaceDataIndex(0, new CommunicationObjectType(name));
        connector->Write(stopmessage);
    }


}
