#include <Centipede.h>
#include <Wire.h>

#include "Machine.h";
#include "LaundryMachine.h";

LaundryMachine * Laundry;
Program * ProgramA;
Program * ProgramB;
HardwareProvider * Hardware;

void setup() {
  
  Serial.begin(9600);
  Serial.flush();

  Hardware = new HardwareProvider();
  ProgramA = new Program(Hardware);
  ProgramB = new Program(Hardware);
  Laundry = new LaundryMachine();

  InitPrograms();
  Empty();

  Laundry->Run(ProgramB);
}

void loop()
{}


void InitPrograms()
{
  ProgramA->AddStep(0, STEP_TURN_RIGHT);
  ProgramA->AddStep(0, STEP_DRAIN_ON);
  ProgramA->AddStep(10, STEP_SPEED_HIGH);
  ProgramA->AddStep(0, STEP_TURN_LEFT);
  ProgramA->AddStep(0, STEP_DRAIN_OFF);
  ProgramA->AddStep(0, STEP_SPEED_HIGH);
  ProgramA->AddStep(20, STEP_SINK_ON);
  ProgramA->AddStep(0, STEP_SINK_OFF);
  ProgramA->AddStep(0, STEP_PROGRAM_END);
}

void Empty()
{
  //Init State and Soap
  ProgramB->AddStep(0, Step_TURN_RIGHT);
  ProgramB->AddStep(0, STEP_LOCK_ON);
  ProgramB->AddStep(0, STEP_DRAIN_ON);
  //Start Rotating
  ProgramB->AddStep(10, STEP_SPEED_MED);
  //Turn Rotation
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  ProgramB->AddStep(10, STEP_TURN_RIGHT);
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  //
  ProgramB->AddStep(0, STEP_SINK_ON);
  //End Program
  ProgramB->AddStep(0, STEP_PROGRAM_END);
}





