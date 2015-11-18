#include <Centipede.h>
#include <Wire.h>

#include "Machine.h";
#include "LaundryMachine.h";
#include "InputProvider.h";

InputProvider * MyInput;
LaundryMachine * Laundry;
Program * ProgramA;
Program * ProgramB;
HardwareProvider * Hardware;
Centipede * CS;

void setup() {
  
  Serial.begin(9600);
  Serial.flush();

  Wire.begin();
  CS->initialize();

  Hardware = new HardwareProvider(CS);
  ProgramA = new Program(Hardware);
  ProgramB = new Program(Hardware);
  Laundry = new LaundryMachine();
  MyInput = new InputProvider(CS);

  InitPrograms();
  Empty();

  Laundry->Run(ProgramB);
}

void loop()
{
  MyInput->UpdateInput();
}


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
  ProgramB->AddStep(0, STEP_TURN_RIGHT);
  ProgramB->AddStep(0, STEP_LOCK_ON);
  ProgramB->AddStep(0, STEP_DRAIN_ON);
  //Start Rotating
  ProgramB->AddStep(10, STEP_SPEED_MED);
  //Turn Rotation
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  ProgramB->AddStep(10, STEP_TURN_RIGHT);
  ProgramB->AddStep(10, STEP_TURN_LEFT);
  //Empty Sink
  ProgramB->AddStep(0, STEP_DRAIN_OFF);
  ProgramB->AddStep(15, STEP_SINK_ON);
  //End Program
  ProgramB->AddStep(0, STEP_PROGRAM_END);
}





