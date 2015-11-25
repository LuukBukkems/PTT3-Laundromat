#ifndef STEP_H
#define STEP_H

#include "HardwareProvider.h"

class Step
{
  public: 
  Step(HardwareProvider * hardware, StepType type, int MyTime);
  Step * GetNext();
  void SetNext(Step * nextStep);
  int GetTime();
  void ExecuteStep();

  private:
  Step * NextStep;
  StepType Type;
  int Time;
  HardwareProvider * Hardware;
  
};

#endif

