#ifndef MYTIMER_H
#define MYTIMER_H

#include <stddef.h>
#include <Arduino.h>

class MyTimer
{
  public:
  MyTimer();
  bool PollTimer();
  void NewTimer(int Time);

  private:
  int StartingTime;
  int EndingTime;
};

#endif
