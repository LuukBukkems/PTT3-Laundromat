#ifndef LAUNDRYMACHINE_H
#define LAUNDRYMACHINE_H

#include "Machine.h";
#include "Program.h";

class LaundryMachine : public Machine
{
  public:
  LaundryMachine();
  void Run(Program * selectedProgram);
  
  private:
  Program * SelectedProgram;
};

#endif

