#include "InputProvider.h"
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

  InputProvider::InputProvider(Centipede * cs): CS(cs)
  { }
  
  void InputProvider::UpdateInput()
  {
    if (CS->digitalRead(IN_IN3) && CS->digitalRead(IN_IN2) && CS->digitalRead(IN_IN1))
    {
      HandleCoins(0);
    }
    
    if(CS->digitalRead(IN_IN3) && !CS->digitalRead(IN_IN2) && !CS->digitalRead(IN_IN1))
    {
      HandleCoins(10);
    }
  
      if(!CS->digitalRead(IN_IN3) && CS->digitalRead(IN_IN2) && !CS->digitalRead(IN_IN1))
    {
      HandleCoins(50);
    }
  
      if(!CS->digitalRead(IN_IN3) && !CS->digitalRead(IN_IN2) && CS->digitalRead(IN_IN1))
    {
      HandleCoins(200);
    }
  }

  void InputProvider::MultiplexOUT(bool GROUP1, bool GROUP2, bool DATAA, bool DATAB, bool DATAC)
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
  
  void InputProvider::HandleCoins(int Coin)
  {
    switch (Coin)
    {
      case 0:
        ClearCoins();        
      break;

      case 10:
        if(_10Coins < 3)
        {
          _10Coins ++;
          TotalMoney += 10;
          
          if(_10Coins == 1)   
              MultiplexOUT(0,0,1,0,0);
          else if(_10Coins == 2)
              MultiplexOUT(0,0,1,1,0);
          else if(_10Coins == 3)
              MultiplexOUT(0,0,1,1,1);
        }
      break;

      case 50:
        if(_50Coins < 3)
        {
          _50Coins ++;
          TotalMoney += 50;
      
          if(_50Coins == 1)
              MultiplexOUT(1,0,1,0,0);
          else if(_50Coins == 2)
              MultiplexOUT(1,0,1,1,0);
          else if(_50Coins == 3)
              MultiplexOUT(1,0,1,1,1);
        }
      break;

      case 200:
        if(_200Coins < 2)
        {
          _200Coins ++;
          TotalMoney += 200;

          if(_200Coins == 1)
            MultiplexOUT(0,1,1,0,0);
          else if(_200Coins == 2)
            MultiplexOUT(0,1,1,1,0);
        }
      break;
    }
  }
  
  void InputProvider::HandleSoap(int Soap)
  {
    
  }
  
  void InputProvider::HandleLock()
  {
    
  }
  
  void InputProvider::HandlePressure()
  {
    
  }

  void InputProvider::ClearCoins()
  {
     MultiplexOUT(0,0,0,0,0);
     MultiplexOUT(1,0,0,0,0);
     MultiplexOUT(0,1,0,0,0);
     _10Coins = 0;
     _50Coins = 0;
     _200Coins = 0;
     TotalMoney = 0;
  }

