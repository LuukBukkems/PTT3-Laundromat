#ifndef CPRESENTATIONPROTOCOL_H_INCLUDED
#define CPRESENTATIONPROTOCOL_H_INCLUDED

/*
==============================================================================

	CPresentationProtocol.h - v1 [11-nov-2015]

		This file is part of the RigidSpectreNet RPCR (Remote Procedure Call Relay) Server project.
		This file is published under the GNU GENERAL PUBLIC LICENSE.
		The exact license can be found on this project's corresponding repository at https://github.com/sangun/RPCServer.

		This project is developed by Marco Schriek (@@39919@@).

	== [ file contents ]

		The RPCServer PresentationProtocol class is defined here.
		This class is made with basic libraries so this class can be used on microcontrollers.

		BIG NOTE: All functions that manipulate lists that store CommunicationObjects use busy waiting by standard.
		If multi-threading is not supported, then you'll need interrupts to keep the methods working.
		Not using interrupts when your program runs on a single thread will cause a deadlock!

==============================================================================
*/

#include "../../CommunicationObject/CommunicationObject.h"

#ifndef _SSTREAM_
	#include <string>
#endif

#ifndef _VECTOR_
	#include <vector>
#endif

//namespace RPCServerBase
//{
	class CommunicationObject;//forward declaration to prevent missing types

	class CPresentationProtocol
	{
		public:

			CPresentationProtocol(void);
			virtual ~CPresentationProtocol(void);

			//Call BufferStarted when processed buffer contains the start symbols of your protocol
			void BufferStarted(void);
			//Call BufferStopped when your protocol's end symbols are detected
			void BufferStopped(void);
			//Call BufferInterrupted when your protocol's met an unexpected problem it cannot deal with.
			void BufferInterrupted(void);

			//A presentation protocol starts working if the start symbols are found within the buffers.
			//When the buffer only has static, is empty or can't find any usable information, then IsWorking returns false
			bool IsWorking(void) const;

			virtual std::string GetProtocolName(void) const;
			virtual std::string GetProtocolModules(void) const = 0;
			virtual std::string GetProtocolVersion(void) const = 0;

			virtual void ProcessChar(char c) = 0;

			virtual void SetStaticClassID(int id) = 0;
			virtual int GetStaticClassID(void) const = 0;

			//should only return true after a CommunicationObject is generated and stored, but is immediately reset the next time processchar is called.

			bool HasBufferedCommunicationObjects(void) const;
			int GetNumBufferedCommunicationObjects(void) const;
			std::vector<CommunicationObject*>* GetBufferedCommunicationObjects(void);

			//returns a juce::String to check whether derived class (protocol) may start reading
			//StartSymbols should return a static const juce::String that indicate the protocol's start.
			virtual const std::string StartSymbols(void) const = 0;

			//returns a juce::String to check whether derived class (protocol) may start reading
			//StartSymbols should return a static const juce::String that indicate the protocol's start.
			virtual const std::string StopSymbols(void) const = 0;

			virtual std::string ToString(const CommunicationObject& communicationObject) const = 0;

		protected:

			void ProcessBuffer(char type, std::string* buffer);
			void ProcessNewCommunicationObject(CommunicationObject* object);

		private:

			std::vector<CommunicationObject*>* bufferedCommunicationObjects;
			bool isWorking;

			void MutexEnter(void);
			void MutexExit(void);
			virtual bool MutexSleep(void);
			bool lock;

			bool hasBufferedCommunicationObjects;
			CommunicationObject *inProgressComObj;
	};
//};

#ifndef PRESENTATIONPROTOCOL_H_INCLUDED
	#define PresentationProtocol CPresentationProtocol
#endif

#endif  // CPRESENTATIONPROTOCOL_H_INCLUDED