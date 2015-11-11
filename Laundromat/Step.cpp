#include "Step.h";

Step::Step()
{
  NextStep = NULL;
}

Step * Step::getNext()
{
  return NextStep;
}

void Step::setNext(Step * nextStep)
{
  if(nextStep != NULL)
  {
    NextStep = nextStep;
  }
}

double Step::getTime()
{
  return Time;
}

void Step::executeStep()
{
    switch(Type)
    {
      case STEP_PROGRAM_END:
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
      break;

      case STEP_SPEED_LOW:
      break;

      case STEP_SPEED_MED:
      break;

      case STEP_SPEED_HIGH:
      break;

      case STEP_TURN_LEFT:
      break;

      case STEP_TURN_RIGHT:
      break;

      case STEP_DRAIN_ON:
      break;

      case STEP_DRAIN_OFF:
      break;

      case STEP_SINK_ON:
      break;

      case STEP_SINK_OFF:
      break;
    }
}



