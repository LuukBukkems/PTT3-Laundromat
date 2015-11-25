#ifndef LAUNDRYMACHINE_H
#define LAUNDRYMACHINE_H

#include "Machine.h";

class Program;

class LaundryMachine : public Machine
{
  public:
  LaundryMachine();
  void Run(Program * selectedProgram);
  
  private:
  Program * SelectedProgram;
};

#endif

