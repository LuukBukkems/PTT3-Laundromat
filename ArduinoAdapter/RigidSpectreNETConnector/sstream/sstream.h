#ifndef _SSTREAM_
#define _SSTREAM_

#include <Stream.h>
#include <string.h>

namespace std
{
	class string : public String
	{
		public:
			string(void) : String()
			{
				
			};

			string(char* d) : String(d)
			{
				
			};
			
			string(String d) : String(d)
			{
				
			};
			
			void clear(void)
			{
				String::remove(0);
			};
			
			size_t find(const std::string& s)
			{
				return find(s.c_str());				
			};
			
			size_t find(const std::string& s, size_t startindex)
			{
				return find(s.c_str(), startindex);				
			};
			
			size_t find(const char* s)
			{
				return String::indexOf(s);	
			}
			
			size_t find(const char* s, size_t startindex)
			{
				return String::indexOf(s, startindex);				
			};
			
			static const size_t npos = -1;
	};
	
	class stringstream : public Stream
	{
		public:
		
			stringstream(void) : strb("") {};
			stringstream(String s) : strb(s), position(0) { };

			// Stream methods
			virtual int available() { return strb.length() - position; };
			virtual int read() { return position < strb.length() ? strb[position++] : -1; };
			virtual int peek() { return position < strb.length() ? strb[position] : -1; };
			virtual void flush() { strb = ""; };
			// Print methods
			virtual size_t write(uint8_t c) { strb += (char)c; };
			
			/*stringstream& operator<<(const long& L)
			{
				str += L;
			};*/
			
			stringstream& operator<<(const double& D)
			{
				
				long k = (long)D;
				
				strb += k;
				k = (long)((D - k)*1000000);//beyond 1 000 000th behind zero, double loses precision
				
				if(D < 0.0)
					{ k*=-1; }
				
				if(k > 0)
				{
					while((k/10)*10 == k)
					{
						k /= 10;
					}
					
					strb += '.';
					strb += k;
				}
				
			};
			
			stringstream& operator<<(const string& s)
			{
				strb += s;
			}
			
			stringstream& operator<<(const char* s)
			{
				strb += s;
			}
			
			String str(void)
			{
				return strb;
			}

		private:
		
			String strb;
			int length;
			int position;
	};
}

#endif //_SSTREAM_