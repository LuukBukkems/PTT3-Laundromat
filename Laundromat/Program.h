#ifndef PROGRAM_H
#define PROGRAM_H

#include "Step.h"

class MyTimer;

class Program
{
  public:
  Program(HardwareProvider * hardware);
  Step * GetCurrentStep();
  bool SetNextStep();
  int GetNrOfSteps();
  void AddStep(int StepTime, StepType Type);
  void Start();
  void DoStep();
  void End();

  private:
  int Counter;
  Step * CurrentStep;
  Step * FirstStep;
  MyTimer * Timer;
  HardwareProvider * Hardware;
};

#endif

