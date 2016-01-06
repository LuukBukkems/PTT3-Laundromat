#include <Centipede.h>
#include <Wire.h>

#include <RigidSpectreNETConnector.h>

#include "Machine.h";
#include "LaundryMachine.h";
#include "InputProvider.h";

FunctionManager fcnmgr;

HardwareProvider * Hardware;
InputProvider * MyInput;

LaundryMachine * Laundry;

Program * ProgramA;
Program * ProgramB;
Program * ProgramC;

Centipede * CS;

bool Running = false;

void StartProgram(int program);
void StopProgram(void);
void GetInformationx(void);

void setup() {
  
  RigidSpectreNETSerialConnector.Connect(19200);//setup Serial baudrate
  RigidSpectreNETSerialConnector.SetProcessor(&fcnmgr);//Set message processor

  Wire.begin();
  CS->initialize();
  pinMode(13, OUTPUT);

  FunctionManagerSetup();

  RigidSpectreNETSerialConnector.IdentifyName("LaundryMachine");

  RigidSpectreNETSerialConnector.IdentifyGroup("Arduino");
  
  Hardware = new HardwareProvider(CS);
  ProgramA = new Program(Hardware);
  ProgramB = new Program(Hardware);
  Laundry = new LaundryMachine();
  MyInput = new InputProvider(CS);

  InitProgA();
  InitProgB();
  //InitProgC();
/*
        Laundry->SelectProgram(ProgramA);
      Running = true;*/
}

void loop()
{   
    if(Running)
    {
      Laundry->Run();
      Hardware->CheckHeat();
    }
  
    MyInput->UpdateInput();
  
    RigidSpectreNETSerialConnector.Read();
}

//************************ Init Programs ********************************//

void InitProgA()
{
  //Prewash
  ProgramA->AddStep(0, STEP_LOCK_ON);
  ProgramA->AddStep(10, STEP_DRAIN_ON);
  ProgramA->AddStep(0, STEP_DRAIN_OFF);
  ProgramA->AddStep(0, STEP_SOAP_1_ON);
  ProgramA->AddStep(0, STEP_SPEED_MED);
  ProgramA->AddStep(10, STEP_TURN_RIGHT);
  ProgramA->AddStep(10, STEP_TURN_LEFT);
  ProgramA->AddStep(0, STEP_SOAP_1_OFF);
  ProgramA->AddStep(0, STEP_SPEED_OFF);
  ProgramA->AddStep(10,STEP_SINK_ON);
  ProgramA->AddStep(0, STEP_SINK_OFF);

  //Init State and Soap
  ProgramA->AddStep(0, STEP_LOCK_ON);
  ProgramA->AddStep(0, STEP_HEAT_MED);
  ProgramA->AddStep(10, STEP_DRAIN_ON);
  ProgramA->AddStep(0, STEP_DRAIN_OFF);
  ProgramA->AddStep(0, STEP_SOAP_2_ON);
  ProgramA->AddStep(0, STEP_SPEED_MED);
  //Turn Rotation
  ProgramA->AddStep(10, STEP_TURN_RIGHT);
  ProgramA->AddStep(10, STEP_TURN_LEFT);
  ProgramA->AddStep(10, STEP_TURN_RIGHT);
  ProgramA->AddStep(10, STEP_TURN_LEFT);
  //Empty Sink
  ProgramA->AddStep(0, STEP_SOAP_2_OFF);
  ProgramA->AddStep(0, STEP_SPEED_OFF);
  ProgramA->AddStep(10, STEP_SINK_ON);
  ProgramA->AddStep(0, STEP_SINK_OFF);
  //------- Init Part 2
  ProgramA->AddStep(0, STEP_HEAT_COLD);
  ProgramA->AddStep(10, STEP_DRAIN_ON);
  ProgramA->AddStep(0, STEP_DRAIN_OFF);
  ProgramA->AddStep(0, STEP_SPEED_MED);
  //Start Rotating
  ProgramA->AddStep(10, STEP_TURN_RIGHT);
  ProgramA->AddStep(10, STEP_TURN_LEFT);
  ProgramA->AddStep(10, STEP_TURN_RIGHT);
  ProgramA->AddStep(10, STEP_TURN_LEFT);
  //Empty Sink
  ProgramA->AddStep(0, STEP_SPEED_OFF);
  ProgramA->AddStep(0, STEP_SINK_ON);
  //------ Part 3
  ProgramA->AddStep(0, STEP_SPEED_HIGH);
  ProgramA->AddStep(5, STEP_TURN_RIGHT);
  ProgramA->AddStep(5, STEP_TURN_LEFT);
  ProgramA->AddStep(5, STEP_TURN_RIGHT);
  ProgramA->AddStep(5, STEP_TURN_LEFT);
  ProgramA->AddStep(5, STEP_TURN_RIGHT);
  ProgramA->AddStep(5, STEP_TURN_LEFT);
  ProgramA->AddStep(0, STEP_SPEED_OFF);
  ProgramA->AddStep(0, STEP_SINK_OFF);
  //End Program
  ProgramA->AddStep(0, STEP_PROGRAM_END);
}

void InitProgB()
{    
  //Prewash
  ProgramB->AddStep(0, STEP_LOCK_ON);
  ProgramB->AddStep(0, STEP_HEAT_MED);
  /*ProgramB->AddStep(10, STEP_DRAIN_ON);
  ProgramB->AddStep(0, STEP_DRAIN_OFF);
  ProgramB->AddStep(0, STEP_SOAP_1_ON);
  ProgramB->AddStep(0, STEP_SPEED_MED);
  ProgramB->AddStep(10, STEP_TURN_RIGHT);
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  ProgramB->AddStep(0, STEP_SOAP_1_OFF);
  ProgramB->AddStep(0, STEP_SPEED_OFF);
  ProgramB->AddStep(10,STEP_SINK_ON);
  ProgramB->AddStep(0, STEP_SINK_OFF);

  //Init State and Soap
  ProgramB->AddStep(0, STEP_LOCK_ON);
  ProgramB->AddStep(10, STEP_DRAIN_ON);
  ProgramB->AddStep(0, STEP_DRAIN_OFF);
  ProgramB->AddStep(0, STEP_SOAP_2_ON);
  ProgramB->AddStep(0, STEP_SPEED_MED);
  //Turn Rotation
  ProgramB->AddStep(10, STEP_TURN_RIGHT);
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  ProgramB->AddStep(10, STEP_TURN_RIGHT);
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  //Empty Sink
  ProgramB->AddStep(0, STEP_SOAP_2_OFF);
  ProgramB->AddStep(0, STEP_SPEED_OFF);
  ProgramB->AddStep(10, STEP_SINK_ON);
  ProgramB->AddStep(0, STEP_SINK_OFF);
  //------- Init Part 2
  ProgramB->AddStep(0, STEP_HEAT_COLD);
  ProgramB->AddStep(10, STEP_DRAIN_ON);
  ProgramB->AddStep(0, STEP_DRAIN_OFF);
  ProgramB->AddStep(0, STEP_SPEED_MED);
  //Start Rotating
  ProgramB->AddStep(10, STEP_TURN_RIGHT);
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  ProgramB->AddStep(10, STEP_TURN_RIGHT);
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  //Empty Sink
  ProgramB->AddStep(0, STEP_SPEED_OFF);
  ProgramB->AddStep(0, STEP_SINK_ON);
  //------ Part 3
  ProgramB->AddStep(0, STEP_SPEED_HIGH);
  ProgramB->AddStep(5, STEP_TURN_RIGHT);
  ProgramB->AddStep(5, STEP_TURN_LEFT);
  ProgramB->AddStep(5, STEP_TURN_RIGHT);
  ProgramB->AddStep(5, STEP_TURN_LEFT);
  ProgramB->AddStep(5, STEP_TURN_RIGHT);
  ProgramB->AddStep(5, STEP_TURN_LEFT);
  ProgramB->AddStep(0, STEP_SPEED_OFF);
  ProgramB->AddStep(0, STEP_SINK_OFF);
  //End Program*/
  ProgramB->AddStep(0, STEP_PROGRAM_END);
}

/*
void InitProgC()
{
  //Prewash
  ProgramC->AddStep(0, STEP_LOCK_ON);
  ProgramC->AddStep(0, STEP_HEAT_MED);
  ProgramC->AddStep(10, STEP_DRAIN_ON);
  ProgramC->AddStep(0, STEP_DRAIN_OFF);
  ProgramC->AddStep(0, STEP_SOAP_1_ON);
  ProgramC->AddStep(0, STEP_SPEED_MED);
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  ProgramC->AddStep(0, STEP_SOAP_1_OFF);
  ProgramC->AddStep(0, STEP_SPEED_OFF);
  ProgramC->AddStep(10,STEP_SINK_ON);
  ProgramC->AddStep(0, STEP_SINK_OFF);

  //Init State and Soap
  ProgramC->AddStep(0, STEP_LOCK_ON);
  ProgramC->AddStep(0, STEP_HEAT_HOT);
  ProgramC->AddStep(20, STEP_DRAIN_ON);
  ProgramC->AddStep(0, STEP_DRAIN_OFF);
  ProgramC->AddStep(0, STEP_SOAP_2_ON);
  ProgramC->AddStep(0, STEP_SPEED_MED);
  //Turn Rotation
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  //Empty Sink
  ProgramC->AddStep(0, STEP_SOAP_2_OFF);
  ProgramC->AddStep(0, STEP_SPEED_OFF);
  ProgramC->AddStep(20, STEP_SINK_ON);
  ProgramC->AddStep(0, STEP_SINK_OFF);
  //------- Init Part 2
  ProgramC->AddStep(0, STEP_HEAT_COLD);
  ProgramC->AddStep(10, STEP_DRAIN_ON);
  ProgramC->AddStep(0, STEP_DRAIN_OFF);
  ProgramC->AddStep(0, STEP_SPEED_MED);
  //Start Rotating
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  ProgramC->AddStep(10, STEP_TURN_RIGHT);
  ProgramC->AddStep(10, STEP_TURN_LEFT);
  //Empty Sink
  ProgramC->AddStep(0, STEP_SPEED_OFF);
  ProgramC->AddStep(0, STEP_SINK_ON);
  //------ Part 3
  ProgramC->AddStep(0, STEP_SPEED_HIGH);
  ProgramC->AddStep(5, STEP_TURN_RIGHT);
  ProgramC->AddStep(5, STEP_TURN_LEFT);
  ProgramC->AddStep(5, STEP_TURN_RIGHT);
  ProgramC->AddStep(5, STEP_TURN_LEFT);
  ProgramC->AddStep(5, STEP_TURN_RIGHT);
  ProgramC->AddStep(5, STEP_TURN_LEFT);
  ProgramC->AddStep(0, STEP_SPEED_OFF);
  ProgramC->AddStep(0, STEP_SINK_OFF);
  //End Program
  ProgramC->AddStep(0, STEP_PROGRAM_END);
}*/

//*************************************** Communication Setup and Fuctions ************************************************//

void FunctionManagerSetup(void)
{
    fcnmgr.AddFunction("StartProgram",  new Delegate1<void, int>(StartProgram));//one argument
    //fcnmgr.AddFunction("StopProgram",  new Delegate0<void>(StopProgram));//zero arguments
    fcnmgr.AddFunction("GetInformation",  new Delegate0<void>(GetInformation));//zero arguments
}

void StartProgram(int program)
{
  if(MyInput->GetLock())
  {
    if(program == 1)
    {
      Laundry->SelectProgram(ProgramA);
      Running = true;
    }
    if(program == 2)
    {
      Laundry->SelectProgram(ProgramB);
      Running = true;
    }
    /*if(program == 3)
    {
      Laundry->SelectProgram(ProgramC);
      Running = true;
    }*/
  }
}

void StopProgram(void)
{
  Laundry->Stop();
  Running = false;
}

void GetInformation(void)
{
  //MachineInformation * Mi;
  //Mi = Hardware->GetMi();
  
  CommunicationObject data;

  data.AddDataIndex(new CommunicationObjectType(ClientName));
  data.AddDataIndex(new CommunicationObjectType("#UpdateInformation"));
  //data.AddDataIndex(new CommunicationObjectType(Mi->Speed));
  
  RigidSpectreNETSerialConnector.Write(data);
  
  /*
    Serial.print("Speed :");
  Serial.println(Mi->Speed);

    Serial.print("Rotation :");
  Serial.println(Mi->Rotation);

    Serial.print("Lock :");
  Serial.println(Mi->Lock);

    Serial.print("Sink :");
  Serial.println(Mi->Sink);

    Serial.print("Drain :");
  Serial.println(Mi->Drain);*/
  
}


