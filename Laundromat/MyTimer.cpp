#include "MyTimer.h";

#include <stddef.h>
#include <Arduino.h>

MyTimer::MyTimer()
{ }

bool MyTimer::PollTimer()
{
  if(millis() >= EndingTime)
  {
    return true;
  }
  return false;
}

void MyTimer::NewTimer(int Time)
{
  StartingTime = millis();
  EndingTime = StartingTime + (Time * 1000);
}



