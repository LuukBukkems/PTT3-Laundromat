#include "Machine.h";

Machine::Machine()
{
  SelectedProgram = NULL;
}

void Machine::Run(Program * selectedProgram)
{
  SelectedProgram = selectedProgram;
}



