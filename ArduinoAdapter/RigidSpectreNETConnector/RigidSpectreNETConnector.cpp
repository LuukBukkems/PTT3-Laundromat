#include "RigidSpectreNETConnector.h"

#include "ServerLibs/CommunicationObject/CommunicationObjectTypes.cpp"
#include "ServerLibs/CommunicationObject/CommunicationObject.cpp"

#include "ServerLibs/PresentationProtocols/Base/CPresentationProtocol.cpp"
#include "ServerLibs/PresentationProtocols/MCOM/MCOM.cpp"

#include "FunctionManager/FunctionManager.cpp"

RigidSpectreNETConnector::RigidSpectreNETConnector(void) : processor(NULL)
{
	
}

void RigidSpectreNETConnector::SetProcessor(FunctionManager* manager)
{
	processor = manager;
}

void RigidSpectreNETConnector::processMessage(char* text, CommunicationObject* message)
{
	if(strlen(text) > 0)
	{
		switch(message->GetSize())
		{
			case 0:
			{
				processor->Call(text);
				break;
			}			
			case 1:
			{
				processor->Call(text, (void*)message->GetRawDataIndex(0)->GetRawDataCopy());
				break;
			}
			
			case 2:
			{
				processor->Call(text, (void*)message->GetRawDataIndex(0)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(1)->GetRawDataCopy());
				break;
			}
			
			case 3:
			{
				processor->Call(text, (void*)message->GetRawDataIndex(0)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(1)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(2)->GetRawDataCopy());
				break;
			}
			
			case 4:
			{
				processor->Call(text, (void*)message->GetRawDataIndex(0)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(1)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(2)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(3)->GetRawDataCopy());
				break;
			}
			
			case 5:
			{
				processor->Call(text, (void*)message->GetRawDataIndex(0)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(1)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(2)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(3)->GetRawDataCopy(),
				(void*)message->GetRawDataIndex(4)->GetRawDataCopy());
				break;
			}
		}
	}
}

void RigidSpectreNETConnector::IdentifyName(const char* devicename)
{
	if(devicename != NULL && strlen(devicename) > 0)
	{
		CommunicationObject identificationmessage;
		identificationmessage.AddDataIndex(new CommunicationObjectType("#Server"));
		identificationmessage.AddDataIndex(new CommunicationObjectType("Identify"));
	
		identificationmessage.AddDataIndex(new CommunicationObjectType("name"));
		identificationmessage.AddDataIndex(new CommunicationObjectType((char*)devicename));
		
		Write(identificationmessage);
	}
}

void RigidSpectreNETConnector::IdentifyGroup(const char* groupname)
{
	if(groupname != NULL && strlen(groupname) > 0)
	{
		CommunicationObject identificationmessage;
		identificationmessage.AddDataIndex(new CommunicationObjectType("#Server"));
		identificationmessage.AddDataIndex(new CommunicationObjectType("Identify"));
	
		identificationmessage.AddDataIndex(new CommunicationObjectType("group"));
		identificationmessage.AddDataIndex(new CommunicationObjectType((char*)groupname));
		
		Write(identificationmessage);
	}
}

RigidSpectreNETSerialConnectorClass::RigidSpectreNETSerialConnectorClass(void) : RigidSpectreNETConnector()
{
	
}

void RigidSpectreNETSerialConnectorClass::Connect(long baudrate)
{
	Serial.begin(baudrate);
}

size_t RigidSpectreNETSerialConnectorClass::Write(char* data)
{
	Serial.print(data);
}

size_t RigidSpectreNETSerialConnectorClass::Write(long data)
{
	Serial.print(data);
}

size_t RigidSpectreNETSerialConnectorClass::Write(double data)
{
	Serial.print(data);
}

size_t RigidSpectreNETSerialConnectorClass::Write(CommunicationObject* data)
{
	if(data != NULL)
	{
		Write(*data);
	}
}

size_t RigidSpectreNETSerialConnectorClass::Write(CommunicationObject& data)
{
	Serial.print(presentationprotocol.ToString(data));
}

void RigidSpectreNETSerialConnectorClass::Read(void)
{	
	if(processor != NULL)
	if(Serial.available() > 0)
	{
		int max_bytes = 200;//read 200 bytes max at a time
		
		while (Serial.available() > 0 && --max_bytes > 0)
		{
			presentationprotocol.ProcessChar(Serial.read());
		}
		
		if(presentationprotocol.HasBufferedCommunicationObjects())
		{			
			std::vector<CommunicationObject*>* messages = presentationprotocol.GetBufferedCommunicationObjects();
			
			for(int i = (messages->size()-1); i >= 0; i--)
			{		
				CommunicationObject* message = (*messages)[i];
			
				if( message->GetSize() > 0)
				{
					const CommunicationObjectType* data = message->ClearDataIndex(0);
					
					if(data->IsString())
					{
						processMessage((char*)data->GetRawDataPointer(), message);
					}
				
				}
			
				delete message;
			}
			
			delete messages;
		}
  }
}

long long atoll(char* txt)
{
	return (long long)atol(txt);
}

RigidSpectreNETSerialConnectorClass RigidSpectreNETSerialConnector;