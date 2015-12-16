/*
==============================================================================

	CPresentationProtocol.cpp - v1 [11-nov-2015]

		This file is part of the RigidSpectreNet RPCR (Remote Procedure Call Relay) Server project.
		This file is published under the GNU GENERAL PUBLIC LICENSE.
		The exact license can be found on this project's corresponding repository at https://github.com/sangun/RPCServer.

		This project is developed by Marco Schriek (@@39919@@).

	== [ file contents ]

		The RPCServer CPresentationProtocol class is declared here.

==============================================================================
*/

#include "CPresentationProtocol.h"

CPresentationProtocol::CPresentationProtocol(void) :
isWorking(false),
inProgressComObj(NULL),
hasBufferedCommunicationObjects(false),
bufferedCommunicationObjects(new std::vector<CommunicationObject*>()),
lock(false)
{
	
}

CPresentationProtocol::~CPresentationProtocol(void)
{
	delete inProgressComObj;
	inProgressComObj = NULL;

	for (unsigned int i = 0; i < bufferedCommunicationObjects->size();i++)
	{
		delete (*bufferedCommunicationObjects)[i];
	}

	delete bufferedCommunicationObjects;
	bufferedCommunicationObjects = NULL;
}

void CPresentationProtocol::ProcessNewCommunicationObject(CommunicationObject* object)
{
	MutexEnter();
	bufferedCommunicationObjects->push_back(object);
	MutexExit();

	hasBufferedCommunicationObjects = true;
	isWorking = true;
}

std::vector<CommunicationObject*>* CPresentationProtocol::GetBufferedCommunicationObjects(void)
{
	MutexEnter();
	std::vector<CommunicationObject*>* result = bufferedCommunicationObjects;
	bufferedCommunicationObjects = new std::vector<CommunicationObject*>();
	MutexExit();

	hasBufferedCommunicationObjects = false;

	return result;
}

bool CPresentationProtocol::HasBufferedCommunicationObjects(void) const
{
	return hasBufferedCommunicationObjects;
}

int CPresentationProtocol::GetNumBufferedCommunicationObjects(void) const
{
	return bufferedCommunicationObjects->size();
}

bool CPresentationProtocol::IsWorking(void) const
{
	return isWorking;
}

void CPresentationProtocol::BufferStarted(void)
{
	isWorking = true;
	delete inProgressComObj;

	inProgressComObj = new CommunicationObject();
}

void CPresentationProtocol::BufferStopped(void)
{
	MutexEnter();
	bufferedCommunicationObjects->push_back(inProgressComObj);
	MutexExit();

	hasBufferedCommunicationObjects = true;

	inProgressComObj = NULL;
	isWorking = false;
}

void CPresentationProtocol::BufferInterrupted(void)
{
	delete inProgressComObj;

	inProgressComObj = NULL;
	isWorking = false;
}

void CPresentationProtocol::ProcessBuffer(char type, std::string* buffer)
{
	if (buffer->length() > 0)
	{
		switch (type)
		{
			case 'N'://Empty spot, Null
			{
				inProgressComObj->AddDataIndex(new CommunicationObjectType(NULL));
				break;
			}
			case 'b'://bit/boolean
			{
				char c1 = buffer->c_str()[0];
				bool b1 = (c1 >= '1' && c1 <= '9' || c1 == 'Y' || c1 == 'y' || c1 == 1);
				inProgressComObj->AddDataIndex(new CommunicationObjectType(b1));
				break;
			}
			case 'c'://a single character
			{
				char c1 = (*buffer)[0];
				inProgressComObj->AddDataIndex(new CommunicationObjectType(c1));
				break;
			}
			case 'A'://an array of characters
			{
				char* a1 = (char*)buffer->c_str();
				inProgressComObj->AddDataIndex(new CommunicationObjectType(a1));
				break;
			}
			case 's'://std::String
			{
				inProgressComObj->AddDataIndex(new CommunicationObjectType(*buffer));
				break;
			}

			case 'i'://8 bit int
			{
				BYTE i1 = (BYTE)atoi(buffer->c_str());
				inProgressComObj->AddDataIndex(new CommunicationObjectType(i1));
				break;
			}
			case 'I'://Int
			{
				int I1 = atoi(buffer->c_str());
				inProgressComObj->AddDataIndex(new CommunicationObjectType(I1));
				break;
			}
			
			case 'j'://Long
			{
				long j1 = atol(buffer->c_str());
				inProgressComObj->AddDataIndex(new CommunicationObjectType(j1));
				break;
			}
			case 'J'://Long long
			{
				long long J1 = atoll(buffer->c_str());
				inProgressComObj->AddDataIndex(new CommunicationObjectType(J1));
				break;
			}
			case 'd'://float/Single
			{
				float d1 = (float)atof(buffer->c_str());
				inProgressComObj->AddDataIndex(new CommunicationObjectType(d1));
				break;
			}
			case 'D'://double
			{
				double D1 = atof(buffer->c_str());
				inProgressComObj->AddDataIndex(new CommunicationObjectType(D1));
				break;
			}
			default:
			{
				//an index of undefined type has been found
				//EXCEPTION?!
				break;
			}
		}
	}
}

std::string CPresentationProtocol::GetProtocolName(void) const
{
	return "UNKNOWN";
}

void CPresentationProtocol::MutexEnter(void)
{
	while(lock && MutexSleep())
	{

	}

	lock = true;
}

void CPresentationProtocol::MutexExit(void)
{
	lock = false;
}

bool CPresentationProtocol::MutexSleep(void)
{
	//busy waiting
	return true;
}