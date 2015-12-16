#ifndef _RIGIDSPECTRENETCONNECTOR_FUNCTIONMANAGER_H_INCLUDED
#define _RIGIDSPECTRENETCONNECTOR_FUNCTIONMANAGER_H_INCLUDED

#include <vector>
#include "../Delegates/Delegates.h"

extern void FunctionManagerSetup(void);

class FunctionManager
{
	public:
	
		FunctionManager(void);
		virtual ~FunctionManager(void);
		
		void AddFunction(const char* functionname, DelegateBase* function);
		
		void* Call(const char* functionname);
		void* Call(const char* functionname, TypeHelper d1);
		void* Call(const char* functionname, TypeHelper d1, TypeHelper d2);
		void* Call(const char* functionname, TypeHelper d1, TypeHelper d2, TypeHelper d3);
		void* Call(const char* functionname, TypeHelper d1, TypeHelper d2, TypeHelper d3, TypeHelper d4);
		void* Call(const char* functionname, TypeHelper d1, TypeHelper d2, TypeHelper d3, TypeHelper d4, TypeHelper d5);
	
	private:
	
		Delegate* FunctionByName(const char* functionname) const;
	
		std::vector<const char*> functionname;
		std::vector<Delegate*>* functions;
	
};

#endif //_RIGIDSPECTRENETCONNECTOR_FUNCTIONMANAGER_H_INCLUDED