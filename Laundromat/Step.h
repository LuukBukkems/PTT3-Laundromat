#ifndef STEP_H
#define STEP_H

#include <stddef.h>
#include "HardwareProvider.h"

class Step
{
  public: 
  Step(HardwareProvider * hardware, StepType type, int MyTime);
  Step * getNext();
  void setNext(Step * nextStep);
  int getTime();
  void executeStep();

  private:
  Step * NextStep;
  StepType Type;
  int Time;
  HardwareProvider * Hardware;
  
};

#endif

