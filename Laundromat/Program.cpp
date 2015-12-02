#include "Program.h";
#include "MyTimer.h"

#include <Arduino.h>;
#include <stddef.h>

Program::Program(HardwareProvider * hardware): Hardware(hardware) 
{
 FirstStep = NULL;
 CurrentStep = FirstStep;
 Timer = new MyTimer();
 Counter = 1;
}

Step * Program::GetCurrentStep()
{
  return CurrentStep;
}

bool Program::SetNextStep()
{
  if(CurrentStep == NULL)
  {
    return false;
  }

  if(CurrentStep->GetNext() != NULL)
  {
    CurrentStep = CurrentStep->GetNext();
    return true;
  }
  
  return false;
}

int Program::GetNrOfSteps()
{
  int Count = 0;
  Step * TempStep = FirstStep;
  while(TempStep != NULL)
  {
    Count ++;
    TempStep = TempStep->GetNext();
  }
  return Count;
}

void Program::AddStep(int StepTime, StepType Type)
{

  Step * S = new Step(Hardware, Type, StepTime);
  if(FirstStep == NULL)
  {
    FirstStep = S;
    CurrentStep = FirstStep;
    return;
  } 
  CurrentStep->SetNext(S);
  CurrentStep = CurrentStep->GetNext();

}

void Program::Start()
{
  CurrentStep = FirstStep;
  int Counter = 1;
  Timer->NewTimer(0);
}

void Program::DoStep()
{
  if(CurrentStep != NULL)
  {
    if(Timer->PollTimer())
    {
     CurrentStep = CurrentStep->GetNext();
     if(CurrentStep != NULL)
     {
      CurrentStep->ExecuteStep();
      Timer->NewTimer(CurrentStep->GetTime());
     }
    }
    return;
  }
}

void Program::End()
{
  if(CurrentStep != NULL)
  {
    if(CurrentStep->GetNext() != NULL)
    {
      while(CurrentStep->GetNext()->GetNext() != NULL)
      {
        CurrentStep = CurrentStep->GetNext();
      }
      Timer->NewTimer(0);
      DoStep();
    }
  }
}

