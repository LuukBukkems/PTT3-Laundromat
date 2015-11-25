#ifndef MYTIMER_H
#define MYTIMER_H

class MyTimer
{
  public:
  MyTimer();
  bool PollTimer();
  void NewTimer(int Time);

  private:
  unsigned long StartingTime;
  unsigned long EndingTime;
};

#endif

