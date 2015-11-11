#include "Machine.h";
#include "LaundryMachine.h";

LaundryMachine * HardwareProvider;
int Capiciteit;
bool Active;
int WaterNeeded;
//ProgramStates State;
int PowerNeeded;

enum ProgramStates
{
  PROGRAM_OFF,
  PROGRAM_PREWASH,
  PROGRAM_MAINWASH,
  PROGRAM_ERROR
};


void setup() {
  HardwareProvider = new LaundryMachine();
  Serial.begin(9600);
  Serial.flush();
}

void loop() {
  
}
