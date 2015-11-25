#ifndef HARDWAREPROVIDER_H
#define HARDWAREPROVIDER_H

class Centipede;

typedef enum StepType
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
  STEP_SINK_OFF,

  STEP_LOCK_ON,
  STEP_LOCK_OFF
};

class HardwareProvider 
{
  public:
  HardwareProvider(Centipede * cs);

  void Fill(int State);
  void Heat(int State);
  void Speed(int State);
  void Turn(int State);
  void Drain(int State);
  void Sink(int State);
  void Lock(int State);
  void EndProgram();
  
  private:
    Centipede * CS;
};

#endif

