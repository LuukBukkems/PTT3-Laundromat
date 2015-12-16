/*
==============================================================================

	MCOM.cpp - v1 [23-okt-2015]

		This file is part of the RigidSpectreNet RPCR (Remote Procedure Call Relay) Server project.
		This file is published under the GNU GENERAL PUBLIC LICENSE.
		The exact license can be found on this project's corresponding repository at https://github.com/sangun/RPCServer.

		This project is developed by Marco Schriek (@@39919@@).

	== [ file contents ]

		The MCOM class is declared here.

==============================================================================
*/

#include "MCOM.h"

PPMCOM::PPMCOM(void) : PresentationProtocol(),
buffer(""),
//
bufferprocessing_variabletype(0)
{

}

const std::string PPMCOM::StartSymbols(void) const
{
	return "(";
}

const std::string PPMCOM::StopSymbols(void) const
{
	return ")";
}

void PPMCOM::ProcessChar(char c)
{
	if (!IsWorking())
	{
		buffer += c;
		size_t index = buffer.find(StartSymbols());

		if (index >= 0 && index != std::string::npos)
		{
			buffer.clear();
			BufferStarted();
		}
	}
	else
	{
		if (bufferprocessing_variabletype == 0)
		{
			switch (c)
			{
				case 'D'://double
				case 'd'://float/Single
				case 'S'://wide string
				case 's'://std::String
				case 'A'://an array of characters
				case 'J'://64 bit int (long long)
				case 'j'://32 bit int (long)
				case 'I'://16 bit int
				case 'i'://8 bit int
				case 'C'://a single wide character
				case 'c'://a single character
				case 'b'://a boolean
				{
					buffer.clear();
					bufferprocessing_variabletype = c;
					break;
				}
				default://static over communication
				{
					buffer += c;

					unsigned int index = buffer.find(StopSymbols());

					if (index >= 0 && index != std::string::npos)
					{
						buffer.clear();
						BufferStopped();
					}

					break;
				}
			}
		}
		else
		{
			if (c == '\4')
			{
				ProcessBuffer(bufferprocessing_variabletype, &buffer);
				buffer.clear();
				bufferprocessing_variabletype = 0;
			}
			else
			{
				buffer += c;
			}
		}
	}
}

//Creates a copy of the derived class protocol
PresentationProtocol* PPMCOM::New(void)
{
	return new PPMCOM();
}

std::string PPMCOM::ToString(const CommunicationObject& communicationObject) const
{
	//Get protocol start symbols
	std::string stringified_obj(StartSymbols());

	for (int i = 0; i <= communicationObject.GetLastIndex(); i++)
	{
		CommunicationObjectType * t = communicationObject.GetDataIndex(i);

		char type = t->GetType();

		stringified_obj += type;
		
		stringified_obj += t->ToString();

		stringified_obj += '\4';

		delete t;
	}

	stringified_obj += StopSymbols();

	return stringified_obj;
}

std::string PPMCOM::GetProtocolName(void) const
{
	return "MCOM";
}
std::string PPMCOM::GetProtocolVersion(void) const
{
	return "0.5";
}
std::string PPMCOM::GetProtocolModules(void) const
{
	return "";
}

void PPMCOM::SetStaticClassID(int id)
{
	ClassTypeID = id;
}

int PPMCOM::GetStaticClassID(void) const
{
	return ClassTypeID;
}

int PPMCOM::ClassTypeID = -1;