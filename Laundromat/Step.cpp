#include "Step.h";
#include <stddef.h>

Step::Step(HardwareProvider * hardware, StepType type, int MyTime):Hardware(hardware), Type(type), Time(MyTime)
{
  NextStep = NULL;
}

Step * Step::GetNext()
{
  return NextStep;
}

void Step::SetNext(Step * nextStep)
{
    NextStep = nextStep;
}

int Step::GetTime()
{
  return Time;
}

void Step::ExecuteStep()
{
    switch(Type)
    {
      case STEP_PROGRAM_END:
        Hardware->EndProgram();
      break;

      case STEP_FILL_EMPTY:
      break;

      case STEP_FILL_LOW:
      break;
  
      case STEP_FILL_MED:
      break;

      case STEP_FILL_FULL:
      break;

      case STEP_HEAT_COLD:
        Hardware->Heat(0);
      break;

      case STEP_HEAT_MED:
        Hardware->Heat(2);
      break;

      case STEP_HEAT_HOT:
        Hardware->Heat(3);
      break;

      case STEP_SPEED_OFF:
        Hardware->Speed(3);
      break;

      case STEP_SPEED_LOW:
        Hardware->Speed(2);
      break;

      case STEP_SPEED_MED:
        Hardware->Speed(1);
      break;

      case STEP_SPEED_HIGH:
        Hardware->Speed(0);
      break;

      case STEP_TURN_LEFT:
        Hardware->Turn(0);
      break;

      case STEP_TURN_RIGHT:
        Hardware->Turn(1);
      break;

      case STEP_DRAIN_ON:
        Hardware->Drain(1);
      break;

      case STEP_DRAIN_OFF:
        Hardware->Drain(0);
      break;

      case STEP_SINK_ON:
        Hardware->Sink(1);
      break;

      case STEP_SINK_OFF:
        Hardware->Sink(0);
      break;

      case STEP_LOCK_ON:
        Hardware->Lock(1);
      break;

      case STEP_LOCK_OFF:
        Hardware->Lock(0);
      break;

      case STEP_SOAP_1_ON:
        Hardware->HandleSoap(1,1);
      break;

      case STEP_SOAP_1_OFF:
        Hardware->HandleSoap(0,1);
      break;

      case STEP_SOAP_2_ON:
        Hardware->HandleSoap(1,2);
      break;

      case STEP_SOAP_2_OFF:
        Hardware->HandleSoap(0,2);
      break;
    }
}



