#include <vector.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(19200);
}

using namespace std;

void loop() {
  
  vector<int*> k;
  
  delay(100);
  
  for(int i = 500; i >= 1; i--)
  {
    k.push_back(new int(i));
  }
  
  for(int i = 0; i < k.size(); i++)
  {
     Serial.println(*(k[i]));
     delete k[i];
  }
  
  k.clear();
}

