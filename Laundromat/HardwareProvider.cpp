#include "HardwareProvider.h"
#include "Centipede.h"

#define OUT_GROUP2      0
#define OUT_GROUP1      1
#define OUT_STROBE      2
#define OUT_KEYSELECT   3
#define OUT_BUZZER      4
#define OUT_HEATER      5
#define OUT_SPEED2      6
#define OUT_SPEED1      7
#define OUT_DATAC       8
#define OUT_DATAB       9
#define OUT_DATAA       10
#define OUT_MOTOR_RL    11
#define OUT_SOAP1       12
#define OUT_SINK        13
#define OUT_DRAIN       14
#define OUT_LOCK        15
#define IN_W2           16
#define IN_W1           17
#define IN_T2           18
#define IN_T1           19
#define IN_IN3          20
#define IN_IN2          21
#define IN_IN1          22
#define IN_IN0          23


HardwareProvider::HardwareProvider(Centipede*  cs): CS(cs)
{
   for (int i = 0; i <= 15; i++) 
  {
    CS->pinMode(i, OUTPUT);
  }

  CS->pinMode(IN_T2, INPUT);
  CS->pinMode(IN_T1, INPUT);
  
  CS->digitalWrite(OUT_GROUP2, LOW);
  CS->digitalWrite(OUT_GROUP1, LOW);
  CS->digitalWrite(OUT_STROBE, LOW);
  CS->digitalWrite(OUT_KEYSELECT, HIGH);
  CS->digitalWrite(OUT_BUZZER, HIGH);
  CS->digitalWrite(OUT_HEATER, HIGH);
  CS->digitalWrite(OUT_SPEED2, HIGH);
  CS->digitalWrite(OUT_SPEED1, HIGH);
  CS->digitalWrite(OUT_DATAC, LOW);
  CS->digitalWrite(OUT_DATAB, LOW);
  CS->digitalWrite(OUT_DATAA, LOW);
  CS->digitalWrite(OUT_MOTOR_RL, LOW);
  CS->digitalWrite(OUT_SOAP1, LOW);
  CS->digitalWrite(OUT_SINK, LOW);
  CS->digitalWrite(OUT_DRAIN, LOW);
  CS->digitalWrite(OUT_LOCK, LOW);

  Mi->Speed = 0;
  Mi->Rotation = false;
  Mi->Lock = false;
  Mi->Heat = false;
  Mi->Sink = false;
  Mi->Drain = false;

  MyHeat = 0;
}

//--------------------------------------------------------------------------------------------//

  void HardwareProvider::Fill(int State)
  {
    
  }
  
  void HardwareProvider::Heat(int State)
  {
   //Mi->Heat = State;
      MyHeat = State;
  }

  void HardwareProvider::CheckHeat()
  {
    int TempHeat = 0;
    if(CS->digitalRead(IN_T1))
    {
      TempHeat += 1;
    }
    if(CS->digitalRead(IN_T2))
    {
      TempHeat += 2;
    }
    if(TempHeat > MyHeat)
    {
      CS->digitalWrite(OUT_HEATER, HIGH);
    }
    else if(TempHeat < MyHeat)
    {
      CS->digitalWrite(OUT_HEATER, LOW);
    }
  }
  
  void HardwareProvider::Speed(int State)
  {
    //Mi->Speed = State;
    switch (State)
    {
      case 0:
        CS->digitalWrite(OUT_SPEED1, LOW);
        CS->digitalWrite(OUT_SPEED2, LOW);
      break;

      case 1:
        CS->digitalWrite(OUT_SPEED1, HIGH);
        CS->digitalWrite(OUT_SPEED2, LOW);
      break;

      case 2:
        CS->digitalWrite(OUT_SPEED1, LOW);
        CS->digitalWrite(OUT_SPEED2, HIGH);
      break;

      case 3:
        CS->digitalWrite(OUT_SPEED1, HIGH);
        CS->digitalWrite(OUT_SPEED2, HIGH);
      break;
    }
  }
  
  void HardwareProvider::Turn(int State)
  {
    //Mi->Rotation = State;
    switch (State)
    {
      case 0:
        CS->digitalWrite(OUT_MOTOR_RL, LOW);
      break;

      case 1:
        CS->digitalWrite(OUT_MOTOR_RL, HIGH);
      break;
    }
  }
  
  void HardwareProvider::Drain(int State)
  {
    //Mi->Drain = State;
    switch (State)
    {
      case 0:
        CS->digitalWrite(OUT_DRAIN, LOW);
      break;

      case 1:
        CS->digitalWrite(OUT_DRAIN, HIGH);
      break;
    }
  }
  
  void HardwareProvider::Sink(int State)
  {
    //Mi->Sink = State;
        switch (State)
    {
      case 0:
        CS->digitalWrite(OUT_SINK, LOW);
      break;

      case 1:
        CS->digitalWrite(OUT_SINK, HIGH);
      break;
    }
  }

  void HardwareProvider::Lock(int State)
  {
    //Mi->Lock = State;
       switch (State)
    {
      case 0:
        CS->digitalWrite(OUT_LOCK, LOW);
      break;

      case 1:
        CS->digitalWrite(OUT_LOCK, HIGH);
      break;
    }
  }

  void HardwareProvider::EndProgram()
  {
    Sink(0);
    Drain(0);
    Speed(3);
    HandleSoap(0,1);
    HandleSoap(0,2);
    Lock(0);
    Heat(0);
  }

  void HardwareProvider::HandleSoap(int State, int Soap)
  {
    if(Soap == 1)
    {
      CS->digitalWrite(OUT_SOAP1, State);
    }
    
    else if(Soap == 2)
    {
      MultiplexOUT(false,true,false,false,State);
    }
  }
  
  void HardwareProvider::MultiplexOUT(bool GROUP1, bool GROUP2, bool DATAA, bool DATAB, bool DATAC)
  {
    CS->digitalWrite(OUT_STROBE,LOW);
  
    CS->digitalWrite(OUT_GROUP2,GROUP2);
    CS->digitalWrite(OUT_GROUP1,GROUP1);
    
    CS->digitalWrite(OUT_DATAA,DATAA);
    CS->digitalWrite(OUT_DATAB,DATAB);
    CS->digitalWrite(OUT_DATAC,DATAC);
    
    delay(80);
    CS->digitalWrite(OUT_STROBE,HIGH);
    delay(80);
  }

  MachineInformation * HardwareProvider::GetMi()
  {
    return Mi;
  }




