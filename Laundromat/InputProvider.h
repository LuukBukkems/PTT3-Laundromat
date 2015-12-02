#ifndef INPUTPROVIDER_H
#define INPUTPROVIDER_H

class Centipede;

class InputProvider
{
  public:
  InputProvider(Centipede *cs);
  
  void UpdateInput();
  bool GetLock();
  
  private:

  Centipede * CS;
  int TotalMoney, Program, _10Coins, _50Coins, _200Coins;
  bool Pressure, DoorLock, Soap1, Soap2;

  void MultiplexOUT(bool GROUP1, bool GROUP2, bool DATAA, bool DATAB, bool DATAC);
  void HandleCoins(int Coin);
  void HandleSoap(int Soap);
  void HandleLock();
  void HandlePressure();

  void ClearCoins();
};

#endif

