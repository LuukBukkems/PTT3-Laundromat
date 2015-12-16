#ifndef _RIGIDSPECTRENETCONNECTOR_H_INCLUDED
#define _RIGIDSPECTRENETCONNECTOR_H_INCLUDED

#include "JuceLibraryCode/AppConfig.h"
#include "JuceLibraryCode/JuceHeader.h"

#include "ServerLibs/CommunicationObject/CommunicationObject.h"
#include "ServerLibs/PresentationProtocols/Base/CPresentationProtocol.h"
#include "ServerLibs/PresentationProtocols/MCOM/MCOM.h"
#include "FunctionManager/FunctionManager.h"


class RigidSpectreNETConnector
{
	public:
	
		RigidSpectreNETConnector(void);
		virtual ~RigidSpectreNETConnector(void);
		
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

		std::string GetAddress(void) const;
		std::string GetPort(void) const;

		std::string GetName(void) const;

		int GetIdentificationStage(void) const;

		bool IsStillConnected(void) const;
		
	protected:
	
		PPMCOM presentationprotocol;
		FunctionManager *processor;

		std::string address;
		std::string port;

		std::string registeredName;

		bool isConnected;

		void identified(CommunicationObject* arguments);
 	
};

class RigidSpectreNETTCPConnector : public RigidSpectreNETConnector
{
	public:
	
		RigidSpectreNETTCPConnector(void);
		virtual ~RigidSpectreNETTCPConnector(void);
		
        bool Connect(const char* address, int port);
		bool Connect(const std::string address, int port);
		void Disconnect(void);
		size_t Write(char* data);
		size_t Write(long data);
		size_t Write(double data);
		
		size_t Write(CommunicationObject* data);
		size_t Write(CommunicationObject& data);
		
		void Read(void);
		
	private:
	
		const int buffersize;
		juce::StreamingSocket* socket;
		char* buffer;
};

#endif
