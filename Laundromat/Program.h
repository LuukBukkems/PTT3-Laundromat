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

  private:
  Step * CurrentStep;
  Step * FirstStep;
  MyTimer * Timer;
  HardwareProvider * Hardware;
};

#endif

