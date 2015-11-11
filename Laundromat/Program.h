#ifndef PROGRAM_H
#define PROGRAM_H

#include <stddef.h>

#include "Step.h"
#include "MyTimer.h"

class Program
{
  public:
  Program();
  Step * GetCurrentStep();
  void SetNextStep();
  int GetNrOfSteps();
  void Start();

  private:
  Step * CurrentStep;
  Step * FirstStep;
  MyTimer * Timer;
};

#endif

