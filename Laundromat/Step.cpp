#include "Step.h";

Step::Step(HardwareProvider * hardware, StepType type, int MyTime)
{
  NextStep = NULL;
  Hardware = hardware;
  Type = type;
  Time = MyTime;
}

Step * Step::getNext()
{
  return NextStep;
}

void Step::setNext(Step * nextStep)
{
    NextStep = nextStep;
}

int Step::getTime()
{
  return Time;
}

void Step::executeStep()
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
      break;

      case STEP_HEAT_MED:
      break;

      case STEP_HEAT_HOT:
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
    }
}



