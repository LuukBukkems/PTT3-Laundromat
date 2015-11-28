/*
==============================================================================

	CommunicationObject.cpp - v1 [23-okt-2015]

		This file is part of the RigidSpectreNet RPCR (Remote Procedure Call Relay) Server project.
		This file is published under the GNU GENERAL PUBLIC LICENSE.
		The exact license can be found on this project's corresponding repository at https://github.com/sangun/RPCServer.

		This project is developed by Marco Schriek (@@39919@@).

	== [ file contents ]

		The CommunicationObject class is declared here.
		This library only uses very basic classes that are easily implementable on microcontrollers if not existing and generally light weight.
		This is to ensure portability of this file so only one (file) version is needed to maintain.

==============================================================================
*/

#include "CommunicationObject.h"

CommunicationObject::CommunicationObject(void) : stillvalid(NULL)
{

}

CommunicationObject::CommunicationObject(const CommunicationObject& copy)
{
	for (int i = (copy.typelessStorage.size()-1); i >= 0; i--)
	{
		typelessStorage.push_back(new CommunicationObjectType(*copy.typelessStorage[i]));
	}

	stillvalid = NULL;
}

CommunicationObject::~CommunicationObject(void)
{
	Reset();
}

bool CommunicationObject::IsDataIndexSet(const unsigned int index) const
{
	if (index >= 0 && index < typelessStorage.size())
	{
		return (typelessStorage[index] != NULL);
	}

	return false;
}

int CommunicationObject::GetLastIndex(void) const
{
	return (typelessStorage.size() - 1);
}

unsigned int CommunicationObject::GetSize(void) const
{
	return typelessStorage.size();
}

void CommunicationObject::Reset(void)
{
	for (unsigned int i = 0; i < typelessStorage.size();i++)
	{
		delete typelessStorage[i];
	}

	typelessStorage.clear();
}

void CommunicationObject::InsertDataIndex(const unsigned int index, CommunicationObjectType* data)
{
	if (data != NULL)
	{
		//std::cout << "Inserting type: " << (char)data->GetType() << std::endl;
		if(index < typelessStorage.size())
		{
			typelessStorage.insert(typelessStorage.begin() + index, data);
		}
		else
		{
			typelessStorage.push_back(data);	
		}
	}
}

void CommunicationObject::ReplaceDataIndex(const unsigned int index, CommunicationObjectType* data)
{
	if (index < typelessStorage.size())
	{
		delete typelessStorage[index];
		typelessStorage[index] = data;
	}
	else
	{
		typelessStorage.push_back(data);
	}
}

void CommunicationObject::AddDataIndex(CommunicationObjectType* data)
{
	if (data != NULL)
	{
		//std::cout << "Adding type: " << (char)data->GetType() << std::endl;
		typelessStorage.push_back(data);
	}
}

CommunicationObjectType* CommunicationObject::ClearDataIndex(const unsigned int index)
{
	CommunicationObjectType* copy = GetDataIndex(index);

	if (copy != NULL)
	{
		RemoveDataIndex(index);
	}

	return copy;
}
void CommunicationObject::RemoveDataIndex(const unsigned int index)
{
	if(IsDataIndexSet(index))
	{
		delete typelessStorage[index];
		typelessStorage.erase(typelessStorage.begin() + index);
	}
}

char CommunicationObject::GetType(const unsigned int index) const
{
	if (IsDataIndexSet(index))
	{
		return typelessStorage[index]->GetType();
	}
	else
	{
		return 'N';
	}
}

size_t CommunicationObject::GetByteSize(const unsigned int index) const
{
	if (IsDataIndexSet(index))
	{
		return typelessStorage[index]->GetByteSize();
	}
	else
	{
		return 0;
	}
}

CommunicationObjectType* CommunicationObject::GetDataIndex(const unsigned int index) const
{
	const CommunicationObjectType* k = GetRawDataIndex(index);

	if (k != NULL)
	{
		return new CommunicationObjectType(*k);
	}

	return NULL;
}

const CommunicationObjectType* CommunicationObject::GetRawDataIndex(const unsigned int index) const
{
	const CommunicationObjectType* result = NULL;

	if (IsDataIndexSet(index))
	{
		const CommunicationObjectType* k = typelessStorage[index];
		result = k;
	}

	return result;
}

CommunicationObject* CommunicationObject::Copy(void) const
{
	return new CommunicationObject(*this);
}

bool CommunicationObject::ExpiredMessage(void) const
{
	return (stillvalid != NULL);
}