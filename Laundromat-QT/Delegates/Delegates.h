#ifndef _DELEGATED_H_INCLUDED
#define _DELEGATED_H_INCLUDED

class TypeHelper
{
	public:
	
		TypeHelper(const bool a)
		{
			bool* b = new bool(a);
			k = b;
			t = 'b';
		};

		TypeHelper(const char a)
		{
			char* s = (char*)malloc(sizeof(char));
			s[0] = a;

			k = (void*)s;
			t = 'c';
		};

		TypeHelper(const float a)
		{
			float* s = (float*)malloc(sizeof(float));
			*s = a;

			k = (void*)s;
			t = 'd';
		};

		TypeHelper(const double a)
		{
			double* s = (double*)malloc(sizeof(double));
			*s = a;

			k = (void*)s;
			t = 'D';
		};

		TypeHelper(const unsigned int a)
		{
			unsigned int* s = (unsigned int*)malloc(sizeof(unsigned int));
			*s = a;

			k = (void*)s;
			t = 'j';
		};

		TypeHelper(const unsigned long a)
		{
			unsigned long* s = (unsigned long*)malloc(sizeof(unsigned long));
			*s = a;

			k = (void*)s;
			t = 'j';
		};

		TypeHelper(const unsigned long long a)
		{
			unsigned long long* s = (unsigned long long*)malloc(sizeof(unsigned long long));
			*s = a;

			k = (void*)s;
			t = 'J';
		};

		TypeHelper(void* a)
		{
			k = NULL;
			t = 'N';
		};

		TypeHelper(const char* a)
		{
			size_t size = (strlen((char*)a) + 1);
			char* s = (char*)malloc(sizeof(char)*size);
			memcpy(s, a, size);

			k = (void*)s;
			t = 'A';
		};
	
		TypeHelper(const int* a)
		{
			unsigned int* s = (unsigned int*)malloc(sizeof(unsigned int));
			*s = *a;

			k = (void*)s;
			t = 'I';
		};

		TypeHelper(const long* a)
		{
			unsigned long* s = (unsigned long*)malloc(sizeof(unsigned long));
			*s = *a;

			k = (void*)s;
			t = 'I';
		};

		TypeHelper(const long long* a)
		{
			unsigned long long* s = (unsigned long long*)malloc(sizeof(unsigned long long));
			*s = *a;

			k = (void*)s;
			t = 'I';
		};
		
		TypeHelper(const float* a)
		{
			float* s = (float*)malloc(sizeof(float));
			*s = *a;

			k = (void*)s;
			t = 'd';
		};

		
		TypeHelper(const double* a)
		{
			double* s = (double*)malloc(sizeof(double));
			*s = *a;

			k = (void*)s;
			t = 'D';
		};
	
		TypeHelper(const unsigned int* a)
		{
			unsigned int* s = (unsigned int*)malloc(sizeof(unsigned int));
			*s = *a;

			k = (void*)s;
			t = 'I';
		};

		TypeHelper(const unsigned long* a)
		{
			unsigned long* s = (unsigned long*)malloc(sizeof(unsigned long));
			*s = *a;

			k = (void*)s;
			t = 'j';
		};
		
		TypeHelper(const unsigned long long* a)
		{
			unsigned long long* s = (unsigned long long*)malloc(sizeof(unsigned long long));
			*s = *a;

			k = (void*)s;
			t = 'J';
		};
		
		TypeHelper(const unsigned char* a)
		{
			size_t size = (strlen((char*)a) + 1);
			char* s = (char*)malloc(sizeof(char)*size);
			memcpy(s, a, size);

			k = (void*)s;
			t = 'A';
		};
		
		TypeHelper(std::string* a)
		{
			std::string* s = new std::string(*a);
			k = (void*)s;
			t = 's';
		};

		static TypeHelper* CreateHelper(const void* a, char type)
		{
			switch(type)
			{
				case 's':
				{
					std::string s((char*)a);
					return new TypeHelper(&s);
					break;
				}
				case 'a':
				{
					return new TypeHelper((char*)a);
					break;
				}
				case 'b':
				{
					return new TypeHelper(*(bool*)a);
				}
				case 'c':
				{
					return new TypeHelper(*(char*)a);
				}
				case 'I':
				{
					return new TypeHelper((int*)a);
				}
				case 'j':
				{
					return new TypeHelper((long*)a);
				}
			}

			return NULL;
		};

		~TypeHelper()
		{
			switch(t)
			{
				case 'A':
				case 'c':
				{
					delete (char*)k;
					break;
				}
				case 'I':
				{
					delete (unsigned int*)k;
					break;
				}
				case 'j':
				{
					delete (unsigned long*)k;
					break;
				}
				case 'J':
				{
					delete (unsigned long long*)k;
					break;
				}
				case 'd':
				{
					delete (float*)k;
					break;
				}
				case 'D':
				{
					delete (double*)k;
					break;
				}
				case 's':
				{
					delete (std::string*)k;
					break;
				}
				case 'b':
				{
					delete (bool*)k;
					break;
				}
			}
		};

		operator std::string() const
		{
			switch(t)
			{
				case 'A':
				case 'c':
				{
					return (char*)k;
					break;
				}
				case 's':
				{
					return *((std::string*)k);
					break;
				}
				case 'b':
				{
					return (*(bool*)k) ? "1" : "0";
					break;
				}
				case 'I':
				{
					char *intStr = (char*)malloc(sizeof(char)*10);
                                        snprintf(intStr, 10, "%d", *(int*)k);
					std::string str(intStr);
					delete intStr;

					return str;
					break;
				}
			}

			return "";  //  Or whatever...
		}

		operator int() const
		{
			switch(t)
			{
				case 'c':
				{
					return ((char*)k)[0];
					break;
				}
				case 'I':
				{
					return *((unsigned int*)k);
					break;
				}
				case 'j':
				{
					return *((unsigned long*)k);
					break;
				}
				case 'J':
				{
					return *((unsigned long long*)k);
					break;
				}
				case 'd':
				{
					return (long long)*((float*)k);
					break;
				}
				case 'D':
				{
					return (long long)*((double*)k);
					break;
				}
				case 'b':
				{
					return (*(bool*)k) ? 1 : 0;
					break;
				}
			}

			return 0;
		}

		operator std::string*() const
		{
			switch(t)
			{
				case 's':
				{
					return ((std::string*)k);
					break;
				}
			}

			return NULL;  //  Or whatever...
		}

		operator const char*() const
		{
			switch(t)
			{
				case 'A':
				case 'c':
				{
					return (const char*)k;
					break;
				}
				case 's':
				{
					return ((std::string*)k)->c_str();
					break;
				}
			}

			return NULL;  //  Or whatever...
		}

		operator void*() const
		{
			return k;  //  Or whatever...
		}

		operator char() const
		{
			switch(t)
			{
				case 'A':
				case 'c':
				{
					return ((char*)k)[0];
					break;
				}
				case 's':
				{
					return (*(std::string*)k)[0];
					break;
				}
				case 'b':
				{
					return (*(bool*)k) ? '1' : '0';
					break;
				}
			}

			return 0;  //  Or whatever...
		}
		
		void* GetPtr(void) const
		{
			return k;
		};

		char GetType(void) const
		{
			return t;
		};
	
	private:
	
		void* k;
		char t;
	
};

class DelegateBase
{
	public:
	
		void SetDataIndex(unsigned int index, TypeHelper* data)
		{			
			if(index < argnum)
			{
				*(dataptrs + index) = data;
			}
		};
		
		virtual void* Call(void) const = 0;
		
		DelegateBase(unsigned int paramsize) : argnum(paramsize), dataptrs((TypeHelper**)malloc(sizeof(TypeHelper*)*paramsize))
		{
			
		}
		
		virtual ~DelegateBase(void)
		{
			delete dataptrs;
			dataptrs = NULL;
		}
	
	protected:
	
		unsigned int argnum;
		TypeHelper** dataptrs;
};

template <typename Ret>
class Callback0
{
  public:
    virtual Ret invoke(void) = 0;
};

template <typename Ret>
class StaticFunctionCallback0 : public Callback0<Ret>
{
  private:
    Ret (*func_)(void);
   
  public:
    StaticFunctionCallback0(Ret (*func)(void))
      : func_(func)
    {
		
	}
     
    virtual Ret invoke(void)
    {
      return (*func_)();
    }
};

template <typename Ret, typename T, typename Method>
class MethodCallback0 : public Callback0<Ret>
{
  private:
    void *object_;
    Method method_;
   
  public:
    MethodCallback0(void *object, Method method)
      : object_(object)
      , method_(method)
    {}
     
    virtual Ret invoke(void)
    {			
      T *obj = static_cast<T *>(object_);
      return (obj->*method_)();
    }
};

template <typename Ret>
class Delegate0 : public DelegateBase
{
  private:
    Callback0<Ret> *callback_;
     
  public:
    Delegate0(Ret (*func)(void))
      : callback_(new StaticFunctionCallback0<Ret>(func)), DelegateBase(0)
    {

	}
	
	void* Call(void) const
	{
		callback_->invoke();
		return 0;
	}
     
    template <typename T, typename Method>
    Delegate0(T *object, Method method)
      :callback_(new MethodCallback0<Ret, T, Method>(object, method)), DelegateBase(0)
    {}
     
    ~Delegate0(void) { delete callback_; }
     
    Ret operator()(void)
    {
      return callback_->invoke();
    }
};

template <typename Ret, typename Param0>
class Callback1
{
  public:
    virtual Ret invoke(Param0 param0) = 0;
};

template <typename Ret, typename Param0>
class StaticFunctionCallback1 : public Callback1<Ret, Param0>
{
  private:
    Ret (*func_)(Param0);
   
  public:
    StaticFunctionCallback1(Ret (*func)(Param0))
      : func_(func)
    {
		
	}
     
    virtual Ret invoke(Param0 param0)
    {
      return (*func_)(param0);
    }
};

template <typename Ret, typename Param0, typename T, typename Method>
class MethodCallback1 : public Callback1<Ret, Param0>
{
  private:
    void *object_;
    Method method_;
   
  public:
    MethodCallback1(void *object, Method method)
      : object_(object)
      , method_(method)
    {}
     
    virtual Ret invoke(Param0 param0)
    {			
      T *obj = static_cast<T *>(object_);
      return (obj->*method_)(param0);
    }
};

template <typename Ret, typename Param0>
class Delegate1 : public DelegateBase
{
  private:
    Callback1<Ret, Param0> *callback_;
     
  public:
    Delegate1(Ret (*func)(Param0))
      : callback_(new StaticFunctionCallback1<Ret, Param0>(func)), DelegateBase(1)
    {

	}
	
	void* Call(void) const
	{		
		callback_->invoke(*dataptrs[0]);
		return 0;
	}
     
    template <typename T, typename Method>
    Delegate1(T *object, Method method)
      :callback_(new MethodCallback1<Ret, Param0, T, Method>(object, method)), DelegateBase(1)
    {}
     
    ~Delegate1(void) { delete callback_; }
     
    Ret operator()(Param0 param0)
    {
      return Call(param0);
    }
};

//
template <typename Ret, typename Param0, typename Param1>
class Callback2
{
  public:
    virtual Ret invoke(Param0 param0, Param1 param1) = 0;
};

template <typename Ret, typename Param0, typename Param1>
class StaticFunctionCallback2 : public Callback2<Ret, Param0, Param1>
{
  private:
    Ret (*func_)(Param0, Param1);
   
  public:
    StaticFunctionCallback2(Ret (*func)(Param0, Param1))
      : func_(func)
    {}
     
    virtual Ret invoke(Param0 param0, Param1 param1)
    {
      return (*func_)(param0, param1);
    }
};

template <typename Ret, typename Param0, typename Param1, typename T, typename Method>
class MethodCallback2 : public Callback2<Ret, Param0, Param1>
{
  private:
    void *object_;
    Method method_;
   
  public:
    MethodCallback2(void *object, Method method)
      : object_(object)
      , method_(method)
    {}
     
    virtual Ret invoke(Param0 param0, Param1 param1)
    {
      T *obj = static_cast<T *>(object_);
      return (obj->*method_)(param0, param1);
    }
};

template <typename Ret, typename Param0, typename Param1>
class Delegate2 : public DelegateBase
{
  private:
    Callback2<Ret, Param0, Param1> *callback_;
     
  public:
    Delegate2(Ret (*func)(Param0, Param1))
      :callback_(new StaticFunctionCallback2<Ret, Param0, Param1>(func)), DelegateBase(2)
    {}
	
	void* Call(void) const
	{		
		callback_->invoke(*dataptrs[0], *dataptrs[1]);
		return 0;
	}
     
    template <typename T, typename Method>
    Delegate2(T *object, Method method)
      :callback_(new MethodCallback2<Ret, Param0, Param1, T, Method>(object, method)), DelegateBase(2)
    {}
     
    ~Delegate2(void) { delete callback_; }
     
    Ret operator()(Param0 param0, Param1 param1)
    {
      return Call(param0, param1);
    }
};

//
template <typename Ret, typename Param0, typename Param1, typename Param2>
class Callback3
{
  public:
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2) = 0;
};

template <typename Ret, typename Param0, typename Param1, typename Param2>
class StaticFunctionCallback3 : public Callback3<Ret, Param0, Param1, Param2>
{
  private:
    Ret (*func_)(Param0, Param1, Param2);
   
  public:
    StaticFunctionCallback3(Ret (*func)(Param0, Param1, Param2))
      : func_(func)
    {}
     
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2)
    {
      return (*func_)(param0, param1, param2);
    }
};

template <typename Ret, typename Param0, typename Param1, typename Param2, typename T, typename Method>
class MethodCallback3 : public Callback3<Ret, Param0, Param1, Param2>
{
  private:
    void *object_;
    Method method_;
   
  public:
    MethodCallback3(void *object, Method method)
      : object_(object)
      , method_(method)
    {}
     
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2)
    {
      T *obj = static_cast<T *>(object_);
      return (obj->*method_)(param0, param1, param2);
    }
};

template <typename Ret, typename Param0, typename Param1, typename Param2>
class Delegate3 : public DelegateBase
{
  private:
    Callback3<Ret, Param0, Param1, Param2> *callback_;
     
  public:
    Delegate3(Ret (*func)(Param0, Param1, Param2))
      :callback_(new StaticFunctionCallback3<Ret, Param0, Param1, Param2>(func)), DelegateBase(3)
    {}
     
	void* Call(void) const
	{		
		callback_->invoke(*dataptrs[0], *dataptrs[1], *dataptrs[2]);
		return 0;
	}
	 
    template <typename T, typename Method>
    Delegate3(T *object, Method method)
      :callback_(new MethodCallback3<Ret, Param0, Param1, Param2, T, Method>(object, method)), DelegateBase(3)
    {}
     
    ~Delegate3(void) { delete callback_; }
     
    Ret operator()(Param0 param0, Param1 param1, Param2 param2)
    {
      return callback_->invoke(param0, param1, param2);
    }
};

//
template <typename Ret, typename Param0, typename Param1, typename Param2, typename Param3>
class Callback4
{
  public:
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2, Param3 param3) = 0;
};

template <typename Ret, typename Param0, typename Param1, typename Param2, typename Param3>
class StaticFunctionCallback4 : public Callback4<Ret, Param0, Param1, Param2, Param3>
{
  private:
    Ret (*func_)(Param0, Param1, Param2, Param3);
   
  public:
    StaticFunctionCallback4(Ret (*func)(Param0, Param1, Param2, Param3))
      : func_(func)
    {}
     
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2, Param3 param3)
    {
      return (*func_)(param0, param1, param2, param3);
    }
};

template <typename Ret, typename Param0, typename Param1, typename Param2, typename Param3, typename T, typename Method>
class MethodCallback4 : public Callback4<Ret, Param0, Param1, Param2, Param3>
{
  private:
    void *object_;
    Method method_;
   
  public:
    MethodCallback4(void *object, Method method)
      : object_(object)
      , method_(method)
    {}
     
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2, Param3 param3)
    {
      T *obj = static_cast<T *>(object_);
      return (obj->*method_)(param0, param1, param2, param3);
    }
};

template <typename Ret, typename Param0, typename Param1, typename Param2, typename Param3>
class Delegate4 : public DelegateBase
{
  private:
    Callback4<Ret, Param0, Param1, Param2, Param3> *callback_;
     
  public:
    Delegate4(Ret (*func)(Param0, Param1, Param2, Param3))
      :callback_(new StaticFunctionCallback4<Ret, Param0, Param1, Param2, Param3>(func)), DelegateBase(4)
    {}
     
    template <typename T, typename Method>
    Delegate4(T *object, Method method)
      :callback_(new MethodCallback4<Ret, Param0, Param1, Param2, Param3, T, Method>(object, method)), DelegateBase(4)
    {}
	
	void* Call(void) const
	{		
		callback_->invoke(*dataptrs[0], *dataptrs[1], *dataptrs[2], *dataptrs[3]);
		return 0;
	}
     
    ~Delegate4(void) { delete callback_; }
     
    Ret operator()(Param0 param0, Param1 param1, Param2 param2, Param3 param3)
    {
      return callback_->invoke(param0, param1, param2, param3);
    }
};

//
template <typename Ret, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
class Callback5
{
  public:
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2, Param3 param3, Param4 param4) = 0;
};

template <typename Ret, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
class StaticFunctionCallback5 : public Callback5<Ret, Param0, Param1, Param2, Param3, Param4>
{
  private:
    Ret (*func_)(Param0, Param1, Param2, Param3, Param4);
   
  public:
    StaticFunctionCallback5(Ret (*func)(Param0, Param1, Param2, Param3, Param4))
      : func_(func)
    {}
     
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2, Param3 param3, Param4 param4)
    {
      return (*func_)(param0, param1, param2, param3, param4);
    }
};

template <typename Ret, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4, typename T, typename Method>
class MethodCallback5 : public Callback5<Ret, Param0, Param1, Param2, Param3, Param4>
{
  private:
    void *object_;
    Method method_;
   
  public:
    MethodCallback5(void *object, Method method)
      : object_(object)
      , method_(method)
    {}
     
    virtual Ret invoke(Param0 param0, Param1 param1, Param2 param2, Param3 param3, Param4 param4)
    {
      T *obj = static_cast<T *>(object_);
      return (obj->*method_)(param0, param1, param2, param3, param4);
    }
};

template <typename Ret, typename Param0, typename Param1, typename Param2, typename Param3, typename Param4>
class Delegate5 : public DelegateBase
{
  private:
    Callback5<Ret, Param0, Param1, Param2, Param3, Param4> *callback_;
     
  public:
    Delegate5(Ret (*func)(Param0, Param1, Param2, Param3, Param4))
      :callback_(new StaticFunctionCallback5<Ret, Param0, Param1, Param2, Param3, Param4>(func)), DelegateBase(5)
    {}
	
	void SetDataIndex(unsigned int index, void* data)
	{
		if(index < argnum)
		{
			dataptrs[index] = data;
		}
	}
	
	void* Call(void) const
	{		
		callback_->invoke(*dataptrs[0], *dataptrs[1], *dataptrs[2], *dataptrs[3], *dataptrs[4]);
		return 0;
	}
     
    template <typename T, typename Method>
    Delegate5(T *object, Method method)
      :callback_(new MethodCallback5<Ret, Param0, Param1, Param2, Param3, Param4, T, Method>(object, method)), DelegateBase(5)
    {}
     
    ~Delegate5(void) { delete callback_; }
     
    Ret operator()(Param0 param0, Param1 param1, Param2 param2, Param3 param3, Param4 param4)
    {
      return Call(param0, param1, param2, param3, param4);
    }
};

class Delegate
{
	public:
	
		Delegate(DelegateBase* f) : ftncntr(f)
		{
			
		};
		
		~Delegate(void)
		{
			delete ftncntr;
			ftncntr = NULL;
		};
		
		void* Call(void) const
		{
			return (void*)ftncntr->Call();
		};
		
		void* Call(TypeHelper &d1) const
		{
			ftncntr->SetDataIndex(0, &d1);
			
			return ftncntr->Call();
		};
		
		void* Call(TypeHelper& d1, TypeHelper& d2) const
		{
			ftncntr->SetDataIndex(0, &d1);
			ftncntr->SetDataIndex(1, &d2);
			
			return ftncntr->Call();
		};
		
		void* Call(TypeHelper& d1, TypeHelper& d2, TypeHelper& d3) const
		{
			ftncntr->SetDataIndex(0, &d1);
			ftncntr->SetDataIndex(1, &d2);
			ftncntr->SetDataIndex(2, &d3);
			
			return ftncntr->Call();
		};
		
		void* Call(TypeHelper& d1, TypeHelper& d2, TypeHelper& d3, TypeHelper& d4) const
		{
			ftncntr->SetDataIndex(0, &d1);
			ftncntr->SetDataIndex(1, &d2);
			ftncntr->SetDataIndex(2, &d3);
			ftncntr->SetDataIndex(3, &d4);
			
			return ftncntr->Call();
		};
		
		void* Call(TypeHelper& d1, TypeHelper& d2, TypeHelper& d3, TypeHelper& d4, TypeHelper& d5) const
		{
			ftncntr->SetDataIndex(0, &d1);
			ftncntr->SetDataIndex(1, &d2);
			ftncntr->SetDataIndex(2, &d3);
			ftncntr->SetDataIndex(3, &d4);
			ftncntr->SetDataIndex(4, &d5);
			
			return ftncntr->Call();
		};
		
		
	private:
	
		DelegateBase* ftncntr;
};

#endif //_DELEGATED_H_INCLUDED
