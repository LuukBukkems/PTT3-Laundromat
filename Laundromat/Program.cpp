#include "Program.h";

#include <Arduino.h>;
#include <stddef.h>

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
  Serial.println(GetNrOfSteps());
  int Counter = 1;

  while(CurrentStep != NULL)
  {
    CurrentStep->ExecuteStep();
        
    Timer->NewTimer(CurrentStep->GetTime());

    while(!Timer->PollTimer())
    {
      delay(10);
    }
    
    CurrentStep = CurrentStep->GetNext();
    
    Serial.print("Last Step was : ");
    Serial.println(Counter++);
     
  }
  Serial.println("Done");
}


