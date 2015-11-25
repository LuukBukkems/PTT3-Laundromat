#include "LaundryMachine.h";

#include <Arduino.h>;
#include <stddef.h>

LaundryMachine::LaundryMachine() : Machine()
{
  Serial.flush();
}

void LaundryMachine::Run(Program * selectedProgram)
{
  SelectedProgram = selectedProgram;
  selectedProgram->Start();
}



