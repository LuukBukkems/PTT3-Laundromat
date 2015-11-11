#ifndef MACHINE_H
#define MACHINE_H

#include <stddef.h>

#include "Program.h";

class Machine
{
  public:
  Machine();
  virtual void Run(Program * selectedProgram) = 0;

  private:
  Program * SelectedProgram;
};

#endif
