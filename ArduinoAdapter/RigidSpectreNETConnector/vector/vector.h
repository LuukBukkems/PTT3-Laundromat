#ifndef _VECTOR_
#define _VECTOR_

#include "Arduino.h"

namespace std
{
	//This vector code was made by zTwix0R : http://www.mpgh.net/forum/showthread.php?t=859803. (7-sept-2014)
	//The code is converted to relatively up to date standards and made in a full Arduino-compatible library. (21-nov-2015)
	
	//Kind regards, Marco S. 
	
/*Basic Vector Class for Arduino IDE*/
	template<typename Data>
	class vector
	{		
		public:
			/*------------CONSTRUCTORS & DESTRUCTORS ----------*/

			vector(void);
			vector(vector const &other);
			vector(Data* arr, size_t len);
			vector(size_t size, Data val = Data());
			
			~vector(void);


			vector const &operator=(vector const &other);
			vector &operator=(vector &other);
			
			vector &operator=(Data arr[]);

			//------------CAPACITY----------
			size_t size(void) const;
			void resize(size_t newsize);
			void resize(size_t newsize, Data val);
			size_t capacity(void) const;
			bool boolean_empty(void) const;
			void reserve(size_t n);
			void shrink_to_fit(void);


			//------------ELEMENT ACCESS----------
			Data& operator[](size_t n) const;
			Data& at(size_t n) const;
			Data& front(void) const;
			Data& back(void) const;
			Data* data(void);
			
			Data* begin(void) const;

			//------------MODIFIERS----------
			void assign(size_t n, const Data& val);
			void push_back(Data const &x);
			void pop_back(void);
			void insert(Data* position, const Data &val);
			void insert(size_t position, const Data &val);
			void erase(Data* item_index);
			void eraseAt(size_t position);
			void eraseAt(size_t first, size_t last);
			
			void swap(vector& x);
			void clear(void);
			
		private:
		
			size_t d_size; // Stores no. of actually stored objects
			size_t d_capacity; // Stores allocated capacity
			Data *d_data; // Stores data
		
			void resize_capacity(size_t newsize);
			void resize_capacity(void);

	};
}

using namespace std;

template<typename Data>
vector<Data>::vector(void): d_size(0),
d_capacity(0),
d_data(NULL)
{
	
}; // Default constructor

template<typename Data>
vector<Data>::vector(vector const &other) : d_size(other.d_size),
d_capacity(other.d_capacity),
d_data(NULL)
{
	if(d_capacity > 0)
	{
		d_data = (Data *)malloc(d_capacity*sizeof(Data));	
		memcpy(d_data, other.d_data, d_size*sizeof(Data));
	}
}; // Copy constuctor

template<typename Data>
vector<Data>::vector(Data* arr, size_t len) : d_size(0),
d_capacity(0),
d_data(NULL)
{
	resize_capacity(len);
}; // Copy constuctor

template<typename Data>
vector<Data>::vector(size_t size, Data val) : d_size(size),
d_capacity(size),
d_data(NULL)
{
	if(d_capacity > 0)
	{
		d_data = (Data *)malloc(d_capacity*sizeof(Data));	
		
		for (size_t s = 0; s < size; s++)
		{
			d_data[s] = val;
		}
	}
}; // Other constructor

template<typename Data>
vector<Data>::~vector(void)
{
	clear();
};

template<typename Data>
vector<Data> const& vector<Data>::operator = (vector<Data> const & other)
{
	free(d_data);
	d_size = other.d_size;
	d_capacity = other.d_capacity;
	d_data = (Data *)malloc(d_capacity*sizeof(Data));
	memcpy(d_data, other.d_data,
		d_size*sizeof(Data));
		
	return *this;
	
}; // Needed for memory management

template<typename Data>
vector<Data>& vector<Data>::operator=(vector<Data> &other) {
	free(d_data);
	d_size = other.d_size;
	d_capacity = other.d_capacity;
	d_data = (Data *)malloc(d_capacity*sizeof(Data));
	memcpy(d_data, other.d_data,
		d_size*sizeof(Data));
	return *this;
}; // Needed for memory management

template<typename Data>
vector<Data>& vector<Data>::operator=(Data arr[]) {
	free(d_data);
	size_t len = sizeof(arr) / sizeof(Data);
	d_size = len;
	d_capacity = len;
	d_data = (Data *)malloc(d_capacity*sizeof(Data));
	memcpy(d_data, arr,
		d_size*sizeof(Data));
		
	return *this;
}; // Needed for memory management


//------------CAPACITY----------
template<typename Data>
size_t vector<Data>::size() const
{
	return d_size;
}; // Size getter	

template<typename Data>
void vector<Data>::resize(size_t newsize)
{
	if(newsize == d_size)
	{
		return;
	}
	
	if(newsize <= 0)
	{
		free(d_data);
		d_capacity = 0;
		d_size = 0;
		d_data = NULL;
	}
	else
	{	
		resize_capacity(newsize);
	}
};

template<typename Data>
void vector<Data>::resize(size_t newsize, Data val)
{
	int prevnew = d_size;

	resize(newsize);
	
	if(newsize > prevnew)
	{
		for (size_t s = prevnew; s < newsize; s++)
		{
			d_data[s] = val;
		}
	}
};

template<typename Data>
size_t vector<Data>::capacity(void) const
{
	return d_capacity;
};

template<typename Data>
bool vector<Data>::boolean_empty(void) const
{
	return (d_size == 0);
};

template<typename Data>
void vector<Data>::reserve(size_t n)
{
	if (n > d_capacity)
	{
		resize_capacity(n);
	}
};

template<typename Data>
void vector<Data>::shrink_to_fit(void)
{
	resize(d_size);
};

//------------ELEMENT ACCESS----------
template<typename Data>
Data& vector<Data>::operator[](size_t n) const
{
	return d_data[n];
}; // Const getter

template<typename Data>
Data& vector<Data>::at(size_t n) const
{
	return d_data[n];
};

template<typename Data>
Data& vector<Data>::front(void) const
{
	return d_data[0];
};

template<typename Data>
Data& vector<Data>::back(void) const
{
	return d_data[d_size - 1];
};

template<typename Data>
Data* vector<Data>::data(void)
{
	return d_data;
};

template<typename Data>
Data* vector<Data>::begin(void) const
{
	return d_data;
}

//------------MODIFIERS----------
template<typename Data>
void vector<Data>::assign(size_t n, const Data& val)
{
	d_size = 0;
	resize(n, val);
};

template<typename Data>
void vector<Data>::push_back(Data const &x)
{
	resize(d_size+1, x);
}; // Adds new value. If needed, allocates more space.

template<typename Data>
void vector<Data>::pop_back(void)
{
	resize(d_size - 1);
};

template<typename Data>
void vector<Data>::insert(Data* position, const Data &val)
{
	size_t pos = (((int)position) - ((int)d_data))/sizeof(Data);
	insert(pos, val);
};


template<typename Data>
void vector<Data>::insert(size_t position, const Data &val)
{
	if(position >= 0)
	{
		while (d_size +1 > d_capacity) resize_capacity();//keep scaling until enough memory is collected
		
		Data *newdata = (Data *)malloc(d_capacity*sizeof(Data));
		memcpy(newdata, d_data, position * sizeof(Data));
		newdata[position] = val;
		memcpy(newdata + position + 1, d_data + position, (d_size - position)* sizeof(Data));
		d_size++;
		free(d_data);
		d_data = (Data *)malloc(d_capacity*sizeof(Data));
		memcpy(d_data, newdata, d_size*sizeof(Data));
	}
};

template<typename Data>
void vector<Data>::erase(Data* item_index)
{
	size_t pos = (((int)item_index) - ((int)d_data))/sizeof(Data);
	
	eraseAt(pos);
};

template<typename Data>
void vector<Data>::eraseAt(size_t position)
{
	Data *newdata = (Data *)malloc(d_capacity*sizeof(Data));
	memcpy(newdata, d_data, position * sizeof(Data));
	
	memcpy(newdata + position, d_data + position + 1, (d_size - position - 1)* sizeof(Data));
	
	free(d_data);
	
	d_data = newdata;
	d_size--;
};

template<typename Data>
void vector<Data>::eraseAt(size_t first, size_t last)
{
	Data *newdata = (Data *)malloc(d_capacity*sizeof(Data));
	memcpy(newdata, d_data, first * sizeof(Data));
	memcpy(newdata + first, d_data + last + 1, (d_size - last - 1)* sizeof(Data));
	free(d_data);
	d_size -= last - first + 1;
	d_data = (Data *)malloc(d_capacity*sizeof(Data));
	memcpy(d_data, newdata, d_size*sizeof(Data));
};

template<typename Data>
void vector<Data>::swap(vector& x)
{
	vector temp = x;
	x = *this;
	d_capacity = temp.capacity();
	d_size = temp.size();
	free(d_data);
	d_data = (Data *)malloc(d_capacity*sizeof(Data));
	memcpy(d_data, temp.data(), d_size*sizeof(Data));
}; //Swaps the data from vector X	

template<typename Data>
void vector<Data>::clear(void)
{
	resize(0);
};

template<typename Data>
void vector<Data>::resize_capacity(size_t newsize)
{	
	d_capacity = ((newsize > 1) ? newsize : 1);
	d_size = d_capacity;
	
	Data *newdata = (Data *)malloc(d_capacity*sizeof(Data));
	memcpy(newdata, d_data, d_capacity * sizeof(Data));
	free(d_data);
	
	d_data = newdata;
}; // Changes d_data's allocated memory size.

template<typename Data>
void vector<Data>::resize_capacity(void)
{	
	resize_capacity(d_capacity * 2);
};// Allocates double the old space

#endif //_VECTOR_