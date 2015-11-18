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

  Step * S = new Step(Hardware, Type, StepTime);
  if(FirstStep == NULL)
  {
    FirstStep = S;
    CurrentStep = FirstStep;
    return;
  } 
  CurrentStep->setNext(S);
  CurrentStep = CurrentStep->getNext();

}

void Program::Start()
{
  CurrentStep = FirstStep;
  Serial.println(GetNrOfSteps());
  int Counter = 1;

  while(CurrentStep != NULL)
  {
    CurrentStep->executeStep();
        
    Timer->NewTimer(CurrentStep->getTime());

    while(!Timer->PollTimer())
    {
      delay(10);
    }
    
    CurrentStep = CurrentStep->getNext();
    
    Serial.print("Last Step was : ");
    Serial.println(Counter++);
     
  }
  Serial.println("Done");
}


