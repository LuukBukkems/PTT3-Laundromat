#ifndef PPMCOM_H_INCLUDED
#define PPMCOM_H_INCLUDED

/*
==============================================================================

	MCOM.h - v1 [23-okt-2015]

		This file is part of the RigidSpectreNet RPCR (Remote Procedure Call Relay) Server project.
		This file is published under the GNU GENERAL PUBLIC LICENSE.
		The exact license can be found on this project's corresponding repository at https://github.com/sangun/RPCServer.

		This project is developed by Marco Schriek (@@39919@@).

	== [ file contents ]

		The MCOM class is defined here.
		This class uses basic libraries for portability to microcontrollers.

==============================================================================
*/

#ifndef CPRESENTATIONPROTOCOL_H_INCLUDED
	#include "../../../RPCServerBase/PresentationProtocol/PresentationProtocol.h"
#endif

/**
	This is a derived PresentationProtocol class.
	This class takes care of processing incoming (possibly) unicode data.
	In essence it tries to parse the format this PresentationProtocol is meant to process.
	If it succeeds, a CommunicationObject is generated with the resulting data.
*/
class PPMCOM : public PresentationProtocol
{
	public:
		PPMCOM(void);

		const std::string StartSymbols(void) const;
		const std::string StopSymbols(void) const;
		void ProcessChar(char c);

		std::string GetProtocolName(void) const;
		std::string GetProtocolVersion(void) const;
		std::string GetProtocolModules(void) const;

		//Creates a copy of the derived class protocol
		PresentationProtocol* New(void);
		void SetStaticClassID(int id);
		int GetStaticClassID(void) const;

		std::string ToString(const CommunicationObject& communicationObject) const;

	private:

		static int ClassTypeID;

		std::string buffer;
		char bufferprocessing_variabletype;

};

#endif  // PPMCOM_H_INCLUDED