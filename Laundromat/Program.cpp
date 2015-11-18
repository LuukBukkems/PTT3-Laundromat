#include "Program.h";
#include <Arduino.h>;

Program::Program(HardwareProvider * hardware)
{
 FirstStep = NULL;
 CurrentStep = FirstStep;
 Timer = new MyTimer();
 Hardware = hardware;
 Serial.flush();
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

  if(CurrentStep->getNext() != NULL)
  {
    CurrentStep = CurrentStep->getNext();
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
    TempStep = TempStep->getNext();
  }
  return Count;
}

void Program::AddStep(int StepTime, StepType Type)
{
  Serial.println("AddStep");
  
  Step * S = new Step(Hardware, Type, StepTime);
  if(FirstStep == NULL)
  {
    FirstStep = S;
    CurrentStep = FirstStep;
    Serial.println(GetNrOfSteps());
    return;
  } 

  Serial.println("NotFirstStep");
  CurrentStep->setNext(S);
  CurrentStep = CurrentStep->getNext();
  Serial.println(GetNrOfSteps());
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
    Serial.println("GoNextStep");
    
  }

  Serial.println("Done");
}


