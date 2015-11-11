#include "Program.h";
#include <Arduino.h>;

Program::Program()
{
 FirstStep = NULL;
 CurrentStep = FirstStep;
 Timer = new MyTimer();
}

Step * Program::GetCurrentStep()
{
  return CurrentStep;
}

void Program::SetNextStep()
{
  if(CurrentStep != NULL)
  {
    CurrentStep = CurrentStep->getNext();
  }
}

int Program::GetNrOfSteps()
{
  int Count = 0;
  Step * TempStep = FirstStep;
  while(TempStep != NULL)
  {
    Count ++;
    TempStep = TempStep->getNext();
  }
  return Count;
}

void Program::Start()
{
  CurrentStep = FirstStep;

  while(CurrentStep != NULL)
  {
    Timer->NewTimer(CurrentStep->getTime());

    CurrentStep->executeStep();

    while(!Timer->PollTimer())
    {
      delay(10);
    }
    
    CurrentStep = CurrentStep->getNext();
    
  }
}


