#include "FunctionManager.h"

	FunctionManager::FunctionManager(void) : functions(new std::vector<Delegate*>())
	{
		
	}
	
	FunctionManager::~FunctionManager(void)
	{
		for(unsigned int s = (functions->size()-1);s >= 0;s--)
		{
			delete (*functions)[s];
		}
		
		delete functions;
		functions = NULL;
	}
	
	void FunctionManager::AddFunction(const char* functionstrname, DelegateBase* function)
	{
		if(strlen(functionstrname) > 0 && function != NULL)
		{			
			for(long s = (((long)functionname.size())-1);s >= 0; s--)
			{
				if(strcmp(functionstrname, functionname[s])  == 0)
				{
					return;
				}
			}
			
			functionname.push_back(functionstrname);
			functions->push_back(new Delegate(function));
		}
	}
	
	Delegate* FunctionManager::FunctionByName(const char* functionstrname) const
	{
		for(unsigned int s = (functionname.size()-1);s >= 0; s--)
		{			
			if(strcmp(functionstrname, functionname[s])  == 0)
			{
				return (*functions)[s];
			}
		}
			
		return NULL;
	}

void* FunctionManager::Call(const char* functionname)
{
	Delegate* f = FunctionByName(functionname);
	
	if(f != NULL)
	{
		return f->Call();
	}
	
	return NULL;
}
	
void* FunctionManager::Call(const char* functionname, TypeHelper d1)
{
	Delegate* f = FunctionByName(functionname);
	
	if(f != NULL)
	{
		return f->Call(d1.GetPtr());
	}
	
	return NULL;
}

void* FunctionManager::Call(const char* functionname, TypeHelper d1, TypeHelper d2)
{
	Delegate* f = FunctionByName(functionname);
	
	if(f != NULL)
	{
		return f->Call(d1.GetPtr(), d2.GetPtr());
	}
	
	return NULL;
}

void* FunctionManager::Call(const char* functionname, TypeHelper d1, TypeHelper d2, TypeHelper d3)
{
	Delegate* f = FunctionByName(functionname);
	
	if(f != NULL)
	{
		return f->Call(d1.GetPtr(), d2.GetPtr(), d3.GetPtr());
	}
	
	return NULL;
}

void* FunctionManager::Call(const char* functionname, TypeHelper d1, TypeHelper d2, TypeHelper d3, TypeHelper d4)
{
	Delegate* f = FunctionByName(functionname);
	
	if(f != NULL)
	{
		return f->Call(d1.GetPtr(), d2.GetPtr(), d3.GetPtr(), d4.GetPtr());
	}
	
	return NULL;
}

void* FunctionManager::Call(const char* functionname, TypeHelper d1, TypeHelper d2, TypeHelper d3, TypeHelper d4, TypeHelper d5)
{
	Delegate* f = FunctionByName(functionname);
	
	if(f != NULL)
	{
		return f->Call(d1.GetPtr(), d2.GetPtr(), d3.GetPtr(), d4.GetPtr(), d5.GetPtr());
	}
	
	return NULL;
}