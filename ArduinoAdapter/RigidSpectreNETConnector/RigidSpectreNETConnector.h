#ifndef _RIGIDSPECTRENETCONNECTOR_H_INCLUDED
#define _RIGIDSPECTRENETCONNECTOR_H_INCLUDED

#include "vector/vector.h"
#include "sstream/sstream.h"
#include "Delegates/Delegates.h"
#include "FunctionManager/FunctionManager.h"

#include "ServerLibs/CommunicationObject/CommunicationObjectTypes.h"
#include "ServerLibs/CommunicationObject/CommunicationObject.h"

#define atoll atol

#include "ServerLibs/PresentationProtocols/Base/CPresentationProtocol.h"
#include "ServerLibs/PresentationProtocols/MCOM/MCOM.h"

#include "Arduino.h"

long long atoll(char*);

class RigidSpectreNETConnector
{
	public:
	
		RigidSpectreNETConnector(void);
		
		virtual size_t Write(char* data) = 0;
		virtual size_t Write(long data) = 0;
		virtual size_t Write(double data) = 0;
		
		virtual size_t Write(CommunicationObject* data) = 0;
		virtual size_t Write(CommunicationObject& data) = 0;
		
		virtual void Read(void) = 0;
		
		void SetProcessor(FunctionManager* manager);
		
		void IdentifyName(const char* devicename);
		void IdentifyGroup(const char* groupname);
		
		void processMessage(char* text, CommunicationObject* message);
		
	protected:
	
		PPMCOM presentationprotocol;
		FunctionManager *processor;
	
};

class RigidSpectreNETSerialConnectorClass : public RigidSpectreNETConnector
{
	public:
	
		RigidSpectreNETSerialConnectorClass(void);
		
		void Connect(long baudrate);
		size_t Write(char* data);
		size_t Write(long data);
		size_t Write(double data);
		
		size_t Write(CommunicationObject* data);
		size_t Write(CommunicationObject& data);
		
		void Read(void);
};

extern RigidSpectreNETSerialConnectorClass RigidSpectreNETSerialConnector;

#endif