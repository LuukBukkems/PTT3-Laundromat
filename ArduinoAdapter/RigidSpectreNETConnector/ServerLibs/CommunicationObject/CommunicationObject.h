#ifndef COMMUNICATIONOBJECT_H_INCLUDED
#define COMMUNICATIONOBJECT_H_INCLUDED

/*
==============================================================================

	CommunicationObject.h - v1 [23-okt-2015]

		This file is part of the RigidSpectreNet RPCR (Remote Procedure Call Relay) Server project.
		This file is published under the GNU GENERAL PUBLIC LICENSE.
		The exact license can be found on this project's corresponding repository at https://github.com/sangun/RPCServer.

		This project is developed by Marco Schriek (@@39919@@).

	== [ file contents ]

		The RPCServer CommunicationObject class is defined here.
		This library only uses very basic classes that are easily implementable on microcontrollers if not existing and generally light weight.
		This is to ensure portability of this file so only one (file) version is needed to maintain.

==============================================================================
*/

#include "CommunicationObjectTypes.h"

#ifndef _VECTOR_
	#include <vector>
#endif

/**
	The CommunicationObject is a collection of wrapped void* that server to allow serialisation and dynamic listing.
	The data stored is interpreted upon the creation of CommunicationObjectType to re-cast the values back to regular variables.
	The object contains various methods to manage the collection or retrieve the stored data.
*/
class CommunicationObject
{
    public:
		CommunicationObject(void);
		CommunicationObject(const CommunicationObject& copy);
		~CommunicationObject(void);
		
		bool IsDataIndexSet(const unsigned int index) const;

		void InsertDataIndex(const unsigned int index, CommunicationObjectType* data);
		void ReplaceDataIndex(const unsigned int index, CommunicationObjectType* data);
		void AddDataIndex(CommunicationObjectType* data);

		/*
			Returns a copy of the container that holds data
		*/
		CommunicationObjectType* GetDataIndex(const unsigned int index) const;

		/*
			Returns the raw pointer object of the container that holds data
			NOTE: Use this function with care; DO not remove returned CommmunicationObjectType!
		*/
		const CommunicationObjectType* GetRawDataIndex(const unsigned int index) const;

		CommunicationObjectType* ClearDataIndex(const unsigned int index);
		void RemoveDataIndex(const unsigned int index);

		char GetType(const unsigned int index) const;
		size_t GetByteSize(const unsigned int index) const;

		void Reset(void);

		int GetLastIndex(void) const;
		unsigned int GetSize(void) const;

		CommunicationObject* Copy(void) const;

		bool ExpiredMessage(void) const;
    
    private:

		std::vector<CommunicationObjectType*> typelessStorage;

		bool* stillvalid;
};

#endif  // COMMUNICATIONOBJECT_H_INCLUDED
