/*
==============================================================================

	CommunicationObjectTypes.cpp - v1 [23-okt-2015]

		This file is part of the RigidSpectreNet RPCR (Remote Procedure Call Relay) Server project.
		This file is published under the GNU GENERAL PUBLIC LICENSE.
		The exact license can be found on this project's corresponding repository at https://github.com/sangun/RPCServer.

		This project is developed by Marco Schriek (@@39919@@).

	== [ file contents ]

		The RPCServer CommunicationObjectType class is declared here.
		This library only uses very basic classes that are easily implementable on microcontrollers if not existing and generally light weight.
		This is to ensure portability of this file so only one (file) version is needed to maintain.

==============================================================================
*/

#include "CommunicationObjectTypes.h"

CommunicationObjectType::CommunicationObjectType(bool& data)
{
	SetData('b', sizeof(bool), &data);
}
CommunicationObjectType::CommunicationObjectType(char& data)
{
	SetData('c', sizeof(char), &data);
}

CommunicationObjectType::CommunicationObjectType(char* data)
{
	//note: if char* is nullptr, it is dealt with in SetData
	SetData('A', sizeof(char)*(strlen(data) + 1), data);
}

CommunicationObjectType::CommunicationObjectType(std::string& data)
{
	const char *c = data.c_str();
	SetData('s', sizeof(char)*(data.length()+1), (void*)c);
}

CommunicationObjectType::CommunicationObjectType(const std::string& data) 
{
	const char *c = data.c_str();
	SetData('s', sizeof(char)*(data.length()+1), (void*)c);
}

CommunicationObjectType::CommunicationObjectType(BYTE& data)
{
	SetData('i', sizeof(BYTE), &data);
}

CommunicationObjectType::CommunicationObjectType(int& data)
{
	SetData('I', sizeof(int), &data);
}

CommunicationObjectType::CommunicationObjectType(long& data)
{
	SetData('j', sizeof(long), &data);
}

CommunicationObjectType::CommunicationObjectType(long long& data)
{
	SetData('J', sizeof(long long), &data);
}

CommunicationObjectType::CommunicationObjectType(float& data)
{
	SetData('d', sizeof(float), &data);
}

CommunicationObjectType::CommunicationObjectType(double& data)
{
	SetData('D', sizeof(double), &data);
}

CommunicationObjectType::CommunicationObjectType(const CommunicationObjectType& cot)
{
	bytesize = cot.bytesize;
	type = cot.type;

	COTdata = cot.GetRawDataCopy();
}

CommunicationObjectType::~CommunicationObjectType(void)
{
	this->bytesize = 0;

	#ifdef Arduino_h
	free(COTdata);
	#else
	delete COTdata;
	#endif
	COTdata = NULL;
}

void CommunicationObjectType::SetData(char type, size_t bytesize, void* data)
{

	if (data == NULL || (bytesize < 1) || type < 48)
	{
		this->bytesize = 0;
		this->type = 'N';
		this->COTdata = NULL;
		return;
	}	

	this->bytesize = bytesize;
	this->type = type;

	void* copy = NULL;

	if (bytesize > 0)
	{
		copy = malloc(bytesize);
		memcpy(copy, data, bytesize);
	}

	this->COTdata = copy;
	
}

size_t CommunicationObjectType::GetByteSize(void) const
{
	return bytesize;
}


char CommunicationObjectType::GetType(void) const
{
	return type;
}

bool CommunicationObjectType::IsString(void) const
{
	return (type == 'A' || type == 's' || type == 'S' || type == 'c');
}

bool CommunicationObjectType::IsNumeric(void) const
{
	return (type == 'c' || type == 'i' || type == 'I' || type == 'j' || type == 'J' || type == 'd' || type == 'D');
}

bool CommunicationObjectType::IsInt(void) const
{
	return (type == 'c' || type == 'i' || type == 'I' || type == 'j' || type == 'J');
}

bool CommunicationObjectType::IsBool(void) const
{
	return (type == 'b');
}

bool CommunicationObjectType::IsNULL(void) const
{
	return (type == 'N');
}

bool CommunicationObjectType::IsTypeSupported(void) const
{
	return (IsNumeric() || IsBool() || IsString() && !IsNULL());
}

void* CommunicationObjectType::GetRawDataCopy(void) const
{
	void* data = NULL;

	if (bytesize > 0)
	{
		data = malloc(bytesize);
		memcpy(data, COTdata, bytesize);
	}

	return data;
}

const void* CommunicationObjectType::GetRawDataPointer(void) const
{
	if (bytesize > 0)
	{
		return COTdata;
	}

	return NULL;
}

std::string CommunicationObjectType::ToString(void) const
{
	return ToString(type, COTdata);
}

std::string CommunicationObjectType::ToString(char type, void* data)
{
	std::stringstream converter;//Although using stringstream is not so performant, it is backwards compatible with older standards such as used in Arduino.

	switch (type)
	{
		case 'b':
		{
			bool b = (bool)(*(bool*)(data));
			converter << b;
			break;
		}
		case 'c':
		{
			char c = (char)(*(char*)(data));
			converter << c;
			break;
		}
		case 'A':
		case 's':
		{
			converter << std::string((char*)data);
			break;
		}
		case 'i':
		{
			int I = (int)(*(char*)(data));
			converter << I;
			break;
		}
		case 'I':
		{
			int I = (int)(*(int*)(data));
			converter << I;
			break;
		}
		case 'j':
		{
			long j = (long)(*(long*)(data));
			converter << j;
			break;
		}
		case 'J':
		{
			long long J = (long long)(*(long long*)(data));
			converter << J;
			break;
		}
		case 'd':
		{
			float d = (float)(*(float*)(data));
			converter << d;
			break;
		}
		case 'D':
		{
			double D = (double)(*(double*)(data));
			converter << D;
			break;
		}
	}

	return converter.str();
}