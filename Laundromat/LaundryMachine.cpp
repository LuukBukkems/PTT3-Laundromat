#include "LaundryMachine.h";

LaundryMachine::LaundryMachine() : Machine()
{
  Serial.flush();
}

void LaundryMachine::Run(Program * selectedProgram)
{
  SelectedProgram = selectedProgram;
  selectedProgram->Start();
}

void LaundryMachine::Test()
{
  Serial.println("asd");
}



