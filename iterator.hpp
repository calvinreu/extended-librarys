#pragma once
#include <vector>

namespace extended{

    template<typename T>
	class normal_iterator
	{
	private:
		T* m_data;
	public:
		normal_iterator(){}
		normal_iterator(T* dataPtr) : m_data(dataPtr) {}
		bool operator< (const normal_iterator<T> &other) const { return m_data  < other.m_data; }
		bool operator> (const normal_iterator<T> &other) const { return m_data  > other.m_data; }
		bool operator<=(const normal_iterator<T> &other) const { return m_data <= other.m_data; }
		bool operator>=(const normal_iterator<T> &other) const { return m_data >= other.m_data; }
		bool operator==(const normal_iterator<T> &other) const { return m_data == other.m_data; }
		bool operator!=(const normal_iterator<T> &other) const { return m_data != other.m_data; }

		t& operator* () { return *m_data; }
		t* operator-> () { return  m_data; }
		t* operator& () const { return  m_data; }

		void operator++(int) { m_data++; return *this; }
		void operator--(int) { m_data--; return *this; }

		void operator+=(const size_t &ammount){ m_data += ammount; }
		void operator-=(const size_t &ammount){ m_data -= ammount; }

		void operator=(const normal_iterator<T> &other){ m_data = other.m_data; }

		normal_iterator<T> operator+(const size_t &ammount) const { return normal_iterator<T>(m_data + ammount); }
		normal_iterator<T> operator-(const size_t &ammount) const { return normal_iterator<T>(m_data - ammount); }

		size_t operator+(const normal_iterator<T> &other){ return normal_iterator<T>(m_data + other.m_data); }
		size_t operator-(const normal_iterator<T> &other){ return normal_iterator<T>(m_data - other.m_data); }
    };
}