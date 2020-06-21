
#include <cstring>
#include <new>
#include <memory>
#include <iostream>
#include <fstream>
#include "vector.hpp"


template<typename T>
extended::vector<T>::vector(){

	m_size=0;
	m_max_size = 0;
	m_data = nullptr;

}

template<typename T>
extended::vector<T>::vector(const size_t &size)
: m_max_size(size), m_size(0){

	//Create an array to save the data
	try
	{
		m_data = memory.allocate(size);
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << e.what() << '\n';
		throw e;
	}

}

template<typename T>
extended::vector<T>::vector(const extended::vector<T> &other)
{
	m_data = memory.allocate(other.m_size);
	copy(other.m_data, m_data, other.m_size);
	m_size = other.m_size;
	m_max_size = m_size;
}

template<typename T>
extended::vector<T>::vector(extended::vector<T> &&other){

	m_data       = other.m_data    ;
	m_size       = other.m_size    ;
	m_max_size   = other.m_max_size;
	other.m_data = nullptr		   ;

}

template<typename T>
extended::vector<T>::~vector(){

	destruct(m_size);
	memory.deallocate(m_data, m_max_size);

}

template<typename T>
void extended::vector<T>::operator=(const extended::vector<T> &other){

	if(other.m_size > m_max_size)
	{
		destruct(m_size);
		memory.deallocate(m_data, m_max_size);

		try
		{
			m_data = memory.allocate(other.m_size);
		}
		catch(const std::bad_alloc& e)
		{
			std::cerr << e.what() << '\n';
			throw e;
		}

		m_size = other.m_size;
		m_max_size = other.m_size;
		copy(other.m_data, m_data, other.m_size);
	}
	else
	{
		destruct(m_size);
		copy(other.m_data, m_data, other.m_size);
		m_size = other.m_size;
	}

}

template<typename T>
void extended::vector<T>::operator=(extended::vector<T> &&other){

	destruct(m_size);
	memory.deallocate(m_data, m_max_size);

	m_data = other.m_data;
	m_size = other.m_size;
	m_max_size = other.m_max_size;
	other.m_data = nullptr;

}

template<typename T>
T& extended::vector<T>::operator*(const vector<T> &other) const
{
	if(this->m_size != other.m_size)
		throw std::runtime_error("cannot multiply vectors with differents sizes");

	T retVal = NULL;

	for(size_t i = 0; i < m_size; i++)
		retVal += m_data[i] * other[i];

	return retVal;
}

template<typename T>
extended::vector<T> extended::vector<T>::operator+(const extended::vector<T> &other) const 
{
	if(m_size < other.m_size){

		vector<T> retVal(other.m_size);

		for(size_t i=0; i < m_size; i++)
			retVal[i]=m_data[i]+other[i];

		for(size_t i=m_size; i < other.m_size; i++)
			retVal[i]=other[i];

		return std::move(retVal);

	}else{

		vector<T> retVal(m_size);

		for(size_t i=0; i < other.m_size; i++)
			retVal[i]=m_data[i]+other[i];

		for(size_t i=other.m_size; i < m_size; i++)
			retVal[i]=m_data[i];

		return std::move(retVal);

	}

}

template<typename T>
extended::vector<T> extended::vector<T>::operator-(const extended::vector<T> &other) const
{

	if(m_size < other.m_size){

		vector<T> retVal(other.m_size);

		for(size_t i=0; i < m_size; i++)
			retVal[i]=m_data[i]-other[i];

		for(size_t i=m_size; i < other.m_size; i++)
			retVal[i]=0-other[i];

		return std::move(retVal);

	}else{

		vector<T> retVal(m_size);

		for(size_t i=0; i < other.m_size; i++)
			retVal[i]=m_data[i]-other[i];

		for(size_t i=other.m_size; i < m_size; i++)
			retVal[i]=m_data[i];

		return std::move(retVal);

	}

}

template<typename T>
void extended::vector<T>::operator-=(const extended::vector<T> &other){

	(*this)=(*this)-other;

}

template<typename T>
void extended::vector<T>::operator+=(const extended::vector<T> &other){

	(*this)=(*this)+other;

}

template<typename T>
T extended::vector<T>::get_vectorValue(){

	T retVal;

	for (size_t i = 0; i < m_size; i++)
		retVal+=m_data[i];

	return retVal;

}

template<typename T>
template<typename... args>
bool extended::vector<T>::push(const args &...arguments){

	if(m_max_size > m_size){
		construct<args...>(arguments... , m_data + m_size);
		m_size++;

		return false;
	}
	else
	{
		T* hpValPtr;

		//creates a new and bigger array
		try
		{
			hpValPtr = memory.allocate(m_size+1);
		}
		catch(const std::bad_alloc& e)
		{
			std::cerr << e.what() << '\n';
			throw e;
		}

		move(hpValPtr);

		destruct(m_size);
		memory.deallocate(m_data, m_size);
		construct<args...>(arguments... , hpValPtr+m_size);

		//change Size
		m_size++;
		//makes the new arrray to the default array
		m_data = hpValPtr;
		return true;
	}

}

template<typename T>
bool extended::vector<T>::push(const T &object)
{
	if(m_max_size > m_size){
		m_data[m_size] = object;
		m_size++;

		return false;
	}
	else
	{
		T* hpValPtr;

		//creates a new and bigger array
		try
		{
			hpValPtr = memory.allocate(m_size+1);
		}
		catch(const std::bad_alloc& e)
		{
			std::cerr << e.what() << '\n';
			throw e;
		}

		move(hpValPtr);

		destruct(m_size);
		memory.deallocate(m_data, m_size);
		m_data[m_size] = object;

		//change Size
		m_size++;
		//makes the new arrray to the default array
		m_data = hpValPtr;
		return true;
	}

}

/*template<typename T>
bool extended::vector<T>::push(T &&otherObject)
{
	if(m_max_size > m_size){
		new(m_data + m_size) T(std::move(otherObject));
		m_size++;

		return false;

	}
	else
	{
		T* hpValPtr;

		//creates a new and bigger array
		try
		{
			hpValPtr = memory.allocate(m_size+1);
		}
		catch(const std::bad_alloc& e)
		{
			std::cerr << e.what() << '\n';
			throw e;
		}

		move(hpValPtr);

		destruct(m_size);
		memory.deallocate(m_data, m_size);

		//makes the new arrray to the default array
		m_data = hpValPtr;
		
		new(m_data + m_size) T(std::move(otherObject));
		//change Size
		m_size++;
		return true;
	}
	
}*/

template<typename T>
void extended::vector<T>::free(const size_t &index){

	destruct(index);

	m_size -= index;

}

template<typename T>
void extended::vector<T>::add_memory(const size_t &index)
{
	T* hpValPtr;//needs new pointer because move and destruct requires original pointer

	//creates a new and bigger array
	try
	{
		hpValPtr = memory.allocate(m_max_size+index);
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << e.what() << '\n';
		throw e;
	}
	move(hpValPtr);
	destruct(m_size);
	memory.deallocate(m_data, m_max_size);
	//change Size
	m_max_size += index;
	//set pointer
	m_data = hpValPtr;
}

template<typename T>
template<typename... args>
bool extended::vector<T>::assign(const size_t &index, const args &...arguments)
{
	bool retval = false;
	if(m_max_size < m_size + index)
	{
		retval = true;
		try
		{
			add_memory(index - (m_max_size - m_size));
		}
		catch(const std::bad_alloc& e)
		{
			throw e;
		}
		
	}

	for (auto i = end(); i < end() + index; i++)
		construct<args...>(arguments... , &i);

	m_size += index;
	
	return retval;
}

template<typename T>
void extended::vector<T>::free_memory(const size_t &index)
{
	T* newValPtr;

	if(m_max_size - index < m_size)
	{
		destruct(m_size-(m_max_size - index));
		m_size = m_max_size - index;
	}

	try
	{
		newValPtr = memory.allocate(m_max_size - index);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "free_memory" << '\n';
	}

	move(newValPtr);

	if(m_data != nullptr)
		memory.deallocate(m_data, m_max_size);

	m_max_size -= index;
	m_data = newValPtr;
}
