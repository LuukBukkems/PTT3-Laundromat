#ifndef LAUNDRYMACHINE_H
#define LAUNDRYMACHINE_H

#include "Machine.h";

class Program;

class LaundryMachine : public Machine
{
  public:
  LaundryMachine();
  void SelectProgram(Program * selectedProgram);
  void Run();
  void Stop();
  
  private:
  Program * SelectedProgram;
  bool Running;
};

#endif

