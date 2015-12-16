#include "RigidSpectreNETConnector.h"

#include "JuceLibraryCode/modules/juce_core/juce_core.cpp"
#include "ServerLibs/CommunicationObject/CommunicationObjectTypes.cpp"
#include "ServerLibs/CommunicationObject/CommunicationObject.cpp"
#include "ServerLibs/PresentationProtocols/Base/CPresentationProtocol.cpp"
#include "ServerLibs/PresentationProtocols/MCOM/MCOM.cpp"

#include "FunctionManager/FunctionManager.cpp"

RigidSpectreNETConnector::RigidSpectreNETConnector(void) : processor(NULL), registeredName(""), address(""), port(""), isConnected(false)
{
	
}

RigidSpectreNETConnector::~RigidSpectreNETConnector(void)
{
}

bool RigidSpectreNETConnector::IsStillConnected(void) const
{
	return isConnected;
}

std::string RigidSpectreNETConnector::GetAddress(void) const
{
	return address;
}

std::string RigidSpectreNETConnector::GetPort(void) const
{
	return port;
}

std::string RigidSpectreNETConnector::GetName(void) const
{
	return registeredName;
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

void RigidSpectreNETConnector::identified(CommunicationObject* arguments)
{
	int size = arguments->GetSize();

	if(size > 1)
	{
		const CommunicationObjectType* param1 = arguments->GetRawDataIndex(0);
		const CommunicationObjectType* param2 = arguments->GetRawDataIndex(1);

		if(param1->IsString())
		{
			const char* message = (const char*)param1->GetRawDataPointer();

			if(strcmp(message, "name") == 0)
			{
				if(size > 2 && param2->IsBool())
				{
					const CommunicationObjectType* param3 = arguments->GetRawDataIndex(2);

					if(param3->IsString())
					{
						bool v = *(bool*)param2->GetRawDataPointer();
						const char* name = (const char*)param3->GetRawDataPointer();

						if(v && strlen(name) > 0)
						{
							std::cout << address << ':' << port << " has identified this client as `" << name << '`' << std::endl;
							registeredName = name;
						}
					}
				}
			}
			else if(strcmp(message, "group") == 0)
			{
				if(size > 2 && param2->IsBool())
				{
					const CommunicationObjectType* param3 = arguments->GetRawDataIndex(2);

					if(param3->IsString())
					{
						bool v = *(bool*)param2->GetRawDataPointer();
						const char* groupname = (const char*)param3->GetRawDataPointer();

						if(v && strlen(groupname) > 0)
						{
							//std::cout << groupname << std::endl;

							//
						}
					}
				}
			}
		}
	}
}

int RigidSpectreNETConnector::GetIdentificationStage(void) const
{
	int stage = -1;

	if(isConnected)
	{
		stage++;

		if(registeredName.length() > 0)
		{
			stage++;
		}
	}

	return stage;
}

RigidSpectreNETTCPConnector::RigidSpectreNETTCPConnector(void) : RigidSpectreNETConnector(),
socket(new juce::StreamingSocket()),
buffer(NULL),
buffersize(200)
{
	
}

RigidSpectreNETTCPConnector::~RigidSpectreNETTCPConnector(void)
{
	
	Disconnect();
	
	delete socket;
	socket = NULL;
}

bool RigidSpectreNETTCPConnector::Connect(const char* address, int port)
{
	return Connect(std::string(address), port);
}

bool RigidSpectreNETTCPConnector::Connect(const std::string address, int port)
{
	std::string target = address;

	if(isConnected)
	{
		socket->close();
	}

	if((isConnected = socket->connect(address, port, 1000)))
	{
		buffer = new char[buffersize];
		this->address = address;
		this->port = juce::String(port).toStdString();
	}
	
	return isConnected;
}

void RigidSpectreNETTCPConnector::Disconnect(void)
{
	address = "";
	port = "";

	registeredName = "";

	if(isConnected)
	{
		CommunicationObject disconnectMessage;
		disconnectMessage.AddDataIndex(new CommunicationObjectType("#server"));
		disconnectMessage.AddDataIndex(new CommunicationObjectType("Disconnect"));
		Write(disconnectMessage);

		socket->close ();
		isConnected = false;

	}
	
	delete buffer;
	buffer = NULL;
}

size_t RigidSpectreNETTCPConnector::Write(char* data)
{
	return socket->write ((void*)data, strlen(data));
}

size_t RigidSpectreNETTCPConnector::Write(long data)
{
	return socket->write ((void*)"J", 1);
}

size_t RigidSpectreNETTCPConnector::Write(double data)
{
	return socket->write ((void*)"L", 1);
}

size_t RigidSpectreNETTCPConnector::Write(CommunicationObject* data)
{
	if(data != NULL)
	{
		return Write(*data);
	}
	return 0;
}

size_t RigidSpectreNETTCPConnector::Write(CommunicationObject& data)
{
	std::string l = presentationprotocol.ToString(data);
	
	const char* t = l.c_str();
	
	return socket->write ((void*)t, l.length());
}

void RigidSpectreNETTCPConnector::Read(void)
{	
	if(socket->waitUntilReady(true, 1))
	{
		int buffernumfilledchars = socket->read(buffer, buffersize, false);

		if(buffernumfilledchars > 0)
		{
			for(int i = 0; i < buffernumfilledchars; i++)
			{
				presentationprotocol.ProcessChar(buffer[i]);
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
							char* FID = (char*)data->GetRawDataPointer();

							if(strlen(FID) == 10 && strcmp(FID, "identified") == 0)
							{
								identified(message);
							}
							else if(processor != NULL)
							{
								processMessage(FID, message);
							}
						}
					
					}
				
					delete message;
				}
				
				delete messages;
			}
		}
	};
}