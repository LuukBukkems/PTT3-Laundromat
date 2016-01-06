#include "LaundryMachine.h"
#include "Program.h"

#include <Arduino.h>
#include <stddef.h>

LaundryMachine::LaundryMachine() : Machine()
{
  Running = false; 
} 

void LaundryMachine::SelectProgram(Program * selectedProgram)
{
    SelectedProgram = selectedProgram;
}
void LaundryMachine::Run()
{
  if(!Running)
  {
    SelectedProgram->Start();
    Running = true;
  }
  
  else if(Running)
  {
     SelectedProgram->DoStep();
  }
}

void LaundryMachine::Stop()
{
  Running = false;
  SelectedProgram->End();
}


