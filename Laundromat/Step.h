#ifndef STEP_H
#define STEP_H

#include <stddef.h>

class Step
{
  public:

enum StepType
{
  STEP_PROGRAM_END,
  
  STEP_FILL_EMPTY,
  STEP_FILL_LOW,
  STEP_FILL_MED,
  STEP_FILL_FULL,
  
  STEP_HEAT_COLD,
  STEP_HEAT_MED,
  STEP_HEAT_HOT,
  
  STEP_SPEED_OFF,
  STEP_SPEED_LOW,
  STEP_SPEED_MED,
  STEP_SPEED_HIGH,

  STEP_TURN_LEFT,
  STEP_TURN_RIGHT,

  STEP_DRAIN_ON,
  STEP_DRAIN_OFF,

  STEP_SINK_ON,
  STEP_SINK_OFF
};
  
  Step();
  Step * getNext();
  void setNext(Step * nextStep);
  double getTime();
  void executeStep();

  private:
  Step * NextStep;
  StepType Type;
  double Time;
};

#endif

