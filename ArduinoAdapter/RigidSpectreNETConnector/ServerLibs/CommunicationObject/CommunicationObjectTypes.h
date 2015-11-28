#ifndef COMMUNICATIONOBJECTTYPES_H_INCLUDED
#define COMMUNICATIONOBJECTTYPES_H_INCLUDED

/*
==============================================================================

	CommunicationObjectTypes.h - v1 [23-okt-2015]

		This file is part of the RigidSpectreNet RPCR (Remote Procedure Call Relay) Server project.
		This file is published under the GNU GENERAL PUBLIC LICENSE.
		The exact license can be found on this project's corresponding repository at https://github.com/sangun/RPCServer.

		This project is developed by Marco Schriek (@@39919@@).

	== [ file contents ]

		The RPCServer CommunicationObjectType class is defined here.
		This library only uses very basic classes that are easily implementable on microcontrollers if not existing and generally light weight.
		This is to ensure portability of this file so only one (file) version is needed to maintain.

==============================================================================
*/

#ifndef _SSTREAM_
	#include <sstream>
#endif


//#include "Arduino.h"

typedef unsigned char BYTE;

/**
	A wrapper around void* used solely to represent the given information and move void* around in a program.
*/
class CommunicationObjectType
{
    public:
		/**
			Wrap around a character
		*/
		CommunicationObjectType(char& data);
		
		/**
			Wrap around an array of characters
		*/
		CommunicationObjectType(char* data);

		/**
			Wrap around a bool
		*/
		CommunicationObjectType(bool& data);

		/**
			Wrap around a an int
		*/
		CommunicationObjectType(int& data);

		/**
			Wrap around a byte
		*/
		CommunicationObjectType(BYTE& data);

		/**
			Wrap around a long
		*/
		CommunicationObjectType(long& data);

		/**
			Wrap around a long long
		*/
		CommunicationObjectType(long long& data);

		/**
			Wrap around a float
		*/
		CommunicationObjectType(float& data);

		/**
			Wrap around a double
		*/
		CommunicationObjectType(double& data);

		/**
			Wrap around a standard (UTF-8) string
		*/
		CommunicationObjectType(std::string& data);
		CommunicationObjectType(const std::string& data);

		CommunicationObjectType(const CommunicationObjectType& cot);
		~CommunicationObjectType(void);


		size_t GetByteSize(void) const;
		char GetType(void) const;
		bool IsString(void) const;
		bool IsNumeric(void) const;
		bool IsInt(void) const;
		bool IsBool(void) const;
		bool IsNULL(void) const;
		
		bool IsTypeSupported(void) const;
		/*
			Returns a void* with newly allocated memory with a copy of COTdata
		*/
		void* GetRawDataCopy(void) const;

		/*
			Returns the void* pointer without making a copy.
			Use this pointer with care!
		*/
		const void* GetRawDataPointer(void) const;

		static std::string ToString(char type, void* data);

		std::string ToString(void) const;
    
    private:

		void SetData(char type, size_t bytesize, void* data);

		size_t bytesize;
		char type;
		void* COTdata;

};

#endif  // COMMUNICATIONOBJECTTYPES_H_INCLUDED
