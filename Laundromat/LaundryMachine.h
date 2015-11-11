#ifndef LAUNDRYMACHINE_H
#define LAUNDRYMACHINE_H

#include <Arduino.h>;
#include <stddef.h>

#include "Machine.h";
#include "Program.h";

class LaundryMachine : public Machine
{
  public:
  LaundryMachine();
  void Run(Program * selectedProgram);
  void Test();

  private:
  Program * SelectedProgram;
};

#endif

