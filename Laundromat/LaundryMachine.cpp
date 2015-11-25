#include "LaundryMachine.h";
#include "Program.h";

#include <Arduino.h>;
#include <stddef.h>

LaundryMachine::LaundryMachine() : Machine()
{ }

void LaundryMachine::Run(Program * selectedProgram)
{
  SelectedProgram = selectedProgram;
  selectedProgram->Start();
}



