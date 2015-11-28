#include <RigidSpectreNETConnector.h>

FunctionManager fcnmgr;

void setup()
{  
  pinMode(13, OUTPUT);
  
  FunctionManagerSetup();
  
  // put your setup code here, to run once:
  RigidSpectreNETSerialConnector.Connect(19200);//setup Serial baudrate
  RigidSpectreNETSerialConnector.SetProcessor(&fcnmgr);//Set message processor
  
  //Big note: Devicename must be unique so make sure that the devicename is not yet used
  RigidSpectreNETSerialConnector.IdentifyName("DeviceName");//Identify with the server who this device is!
  
  RigidSpectreNETSerialConnector.IdentifyGroup("Arduino");
}

void loop()
{
   //
    /*
    
    // Creating a message to send back to the server:
    
      CommunicationObject k;
    
      //add some data
      int a = 5;
      int b = 7;
      
      std::string redundant_data("some redundant data!");
      
      k.AddDataIndex(new CommunicationObjectType("#Server"));//receivername: string data, only exception due to char*
      k.AddDataIndex(new CommunicationObjectType("example"));//functionname
      k.AddDataIndex(new CommunicationObjectType(a));//reference variable (data a = int)
      k.AddDataIndex(new CommunicationObjectType(b));//reference variable (data b = int)
      k.AddDataIndex(new CommunicationObjectType(redundant_data));
      // put your main code here, to run repeatedly:
      
      RigidSpectreNETSerialConnector.Write(k);
      
    //Sending raw Serial data:
    
      RigidSpectreNETSerialConnector.Write("data!");
      
      delay(10000);
    //*/
  // 
 
  RigidSpectreNETSerialConnector.Read();//Call read to poll for incoming data
}
