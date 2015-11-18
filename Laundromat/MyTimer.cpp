#include "MyTimer.h";

MyTimer::MyTimer()
{
}

bool MyTimer::PollTimer()
{
  if(millis() >= EndingTime)
  {
    Serial.println(StartingTime);
    Serial.println(EndingTime);
    Serial.println(EndingTime - StartingTime);
    return true;
  }
  return false;
}

void MyTimer::NewTimer(int Time)
{
  StartingTime = millis();
  EndingTime = StartingTime + (Time * 1000);
}



