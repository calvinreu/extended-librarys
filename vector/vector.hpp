#pragma once

#include <initializer_list>
#include <memory>
#include <new>
#include <iostream>
#include <string.h>

namespace extended{

	template<typename T>
	class matrix;//class from extended::matrix lib

	//Container with Data types
	template<typename T>
	class vector{
	public:
		template<typename t>
		class iterator;

		typedef iterator<const T> const_iterator;
		typedef iterator<T> normal_iterator;
	private:
		//definitions

		std::allocator<T> memory;
		T* m_data;
		size_t m_size;
		size_t m_max_size;

		template<typename t = T>
		inline typename std::enable_if<!std::is_trivially_destructible<t>::value>::type
			destruct(const size_t &index){/*do nothing*/}

		template<typename t = T>
		inline typename std::enable_if<std::is_trivially_destructible<t>::value>::type
			destruct(const size_t &index){
				for(auto i = this->end(); i > this->end() - index; i--)
					i->~T();
			}

		template<typename t = T>
		inline typename std::enable_if<!std::is_trivially_move_constructible<t>::value>::type
			move(T* destination){ memmove(destination, m_data, m_size); }

		template<typename t = T>
		inline typename std::enable_if<std::is_trivially_move_constructible<t>::value>::type
			move(T* destination){
				for (size_t i = 0; i < m_size; i++)
					new(destination + i) T(std::move(m_data[i]));	
			}

		template<typename... args, typename t = T>
		inline typename std::enable_if<std::is_trivially_default_constructible<t>::value>::type
			construct(const args &...arguments, T* destination){ /* do nothing */}

		template<typename... args, typename t = T>
		inline typename std::enable_if<!std::is_trivially_default_constructible<t>::value>::type
			construct(const args &...arguments, T* destination){ new(destination) T(arguments...); }

		template<typename t = T>
		inline typename std::enable_if<!std::is_trivially_copy_constructible<t>::value>::type
			copy(const T* source, T* destination, const size_t &size) { memcpy(destination, source, size*sizeof(T)); }

		template<typename t = T>
		inline typename std::enable_if<std::is_trivially_copy_constructible<t>::value>::type
			copy(const T* source, T* destination, const size_t &size){
				for (size_t i = 0; i < size; i++)
					new(destination + i) T(source[i]);
			}
	public:
		template<typename t>
		class iterator
		{
		private:
			t* m_data;
			iterator(T* dataPtr) : m_data(dataPtr) {}
		public:
			iterator(){}
			bool operator< (const vector<T>::iterator<t> &other) const { return m_data  < other.m_data; }
			bool operator> (const vector<T>::iterator<t> &other) const { return m_data  > other.m_data; }
			bool operator<=(const vector<T>::iterator<t> &other) const { return m_data <= other.m_data; }
			bool operator>=(const vector<T>::iterator<t> &other) const { return m_data >= other.m_data; }
			bool operator==(const vector<T>::iterator<t> &other) const { return m_data == other.m_data; }
			bool operator!=(const vector<T>::iterator<t> &other) const { return m_data != other.m_data; }

			t& operator* () { return *m_data; }
			t* operator-> () { return  m_data; }
			t* operator& () const { return  m_data; }

			void operator++(int) { m_data++; }
			void operator--(int) { m_data--; }

			void operator+=(const size_t &ammount){ m_data += ammount; }
			void operator-=(const size_t &ammount){ m_data -= ammount; }

			void operator=(const vector<T>::iterator<t> &other){ m_data = other.m_data; }

			vector<T>::iterator<t> operator+(const size_t &ammount) const { return vector<T>::iterator<t>(m_data + ammount); }
			vector<T>::iterator<t> operator-(const size_t &ammount) const { return vector<T>::iterator<t>(m_data - ammount); }

			size_t operator+(const vector<T>::iterator<t> &other){ return vector<T>::normal_iterator(m_data + other.m_data); }
			size_t operator-(const vector<T>::iterator<t> &other){ return vector<T>::normal_iterator(m_data - other.m_data); }

			friend vector;

		};

		vector();
		vector(const size_t &size);
		vector(const std::initializer_list<T> &initData);
		~vector();
		vector(   vector<T> &&other);
		vector(const vector<T> &other);

		T& operator[](const size_t &index){ return m_data[index]; }
		const T& operator[](const size_t &index) const { return m_data[index]; }
		T& operator*(const vector<T> &other) const;
		vector<T> operator*(const extended::matrix<T> &other) const;
		vector<T> operator+(const vector<T> &other) const;
		vector<T> operator-(const vector<T> &other) const;
		void operator-=(const vector<T> &other);
		void operator+=(const vector<T> &other);
		void operator=(const vector<T>  &other);
		void operator=(	   vector<T> &&other);

		const size_t& size() const { return m_size; }
		const size_t& max_size() const { return m_max_size; }
		T get_vectorValue();
		void add_memory(const size_t &index);

		template<typename... args>
		bool assign(const size_t &index, const args &...arguments);

		template<typename... args>
		bool push(const args &...arguments);
		//bool push(T &&moveObject);
		bool push(const T &object);
		void free(const size_t &index);
		void free_memory(const size_t &index);

		vector<T>::normal_iterator begin (){ return vector<T>::normal_iterator(m_data            ); }
		vector<T>::normal_iterator end   (){ return vector<T>::normal_iterator(m_data + m_size   ); }
		vector<T>::normal_iterator rbegin(){ return vector<T>::normal_iterator(m_data + m_size -1); }
		vector<T>::normal_iterator rend  (){ return vector<T>::normal_iterator(m_data - 1        ); }

		vector<T>::const_iterator begin () const { return vector<T>::const_iterator(m_data            ); }
		vector<T>::const_iterator end   () const { return vector<T>::const_iterator(m_data + m_size   ); }
		vector<T>::const_iterator rbegin() const { return vector<T>::const_iterator(m_data + m_size -1); }
		vector<T>::const_iterator rend  () const { return vector<T>::const_iterator(m_data - 1        ); }

		T& first(){ return *m_data; }
		T& last() { return *(m_data + m_size -1); }

		T& first() const { return *m_data; }
		T& last() const { return *(m_data + m_size -1); }

		//only use these functions if you know how the library works
		T* get_ValPtr(){ return m_data; }
		const T* get_ValPtr() const { return m_data; }
		void new_size(const size_t &size){ m_size = size; }
	};
}	
