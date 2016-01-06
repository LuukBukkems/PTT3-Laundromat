#ifndef MACHINE_H
#define MACHINE_H

#include "Program.h"

class Machine
{
  public:
  Machine();
  virtual void SelectProgram(Program * selectedProgram) = 0;
  virtual void Run() = 0;
  virtual void Stop() = 0;
  
  private:
  Program * SelectedProgram;
  bool Running;
};

#endif

