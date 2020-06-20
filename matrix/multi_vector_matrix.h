#pragma once
#include <extended/vector>
#include <extended/matrix>
#include <error.h>
#include <initializer_list>
#include <iostream>


namespace extended{

	template<typename T>
	class multi_vector_matrix{
	private:
		//data container and data management
		extended::vector<extended::vector<<T>> data;

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

		multi_vector_matrix(){}
		multi_vector_matrix(const size_t &rowCount, const size_t &rowSize);//constructor only allocates memory to initialize fill operator = also works but will destroy the matrix first
		multi_vector_matrix(const std::initializer_list<std::initializer_list<T>> initData);
		~multi_vector_matrix(){}//do nothing data already deallocates memory
		multi_vector_matrix(      multi_vector_matrix<T> &&other) : data(std::move(other.data)){}
		multi_vector_matrix(const multi_vector_matrix<T>  &other) : data(other.data){}

        void operator=(const multi_vector_matrix<T>  &other){ data = other.data; }
		void operator=(	  multi_vector_matrix<T> &&other){ data = std::move(other.data);}
        void operator=(const std::initializer_list<std::initializer_list<T>> initData){ this->data = std::move(extended::multi_vector_matrix(initData)); }

		T& operator()(const size_t &row, const size_t &index){ return data[row][index]; }
		const T& operator()(const size_t &row, const size_t &index) const { return data[row][index]; }

		multi_vector_matrix<T> operator+(const multi_vector_matrix<T> &other) const;
		multi_vector_matrix<T> operator-(const multi_vector_matrix<T> &other) const;
		multi_vector_matrix<T> operator*(const multi_vector_matrix<T> &other) const;
		multi_vector_matrix<T> operator*(const T &scalar) const;//scalar multiplication
		//multi_vector_matrix<T> operator/(const multi_vector_matrix<T> &other) const;
		//multi_vector_matrix<T> operator%(const multi_vector_matrix<T> &other) const; not sure if usefull or what it shoulkd do

		void operator-=(const multi_vector_matrix<T> &other){ *this = (*this) - other; }
		void operator+=(const multi_vector_matrix<T> &other){ *this = (*this) + other; }
		void operator*=(const multi_vector_matrix<T> &other){ *this = (*this) * other; }
		void operator*=(const T &other){ *this = (*this) * other; }
		//void operator/=(const multi_vector_matrix<T>  &other){ *this = (*this) / other; } //not sure if usefull or what it should do

		const size_t& row_size () const { return data.first.size(); }
		const size_t row_count() const { return data.size(); }

		template<typename to>
		multi_vector_matrix<to> cast() const;
		void recreate(const size_t &rowCount, const size_t &rowSize);// deletes all data from the matrix
			  extended::vector<T> get_data()       {return data; }
		const extended::vector<T> get_data() const {return data; }
		template<typename... args>
		inline void fill(args &...arguments);//if it isnt trivially_default_constructible arguments arent used

		//iterator functions
		inline typename extended::vector<T>::normal_iterator begin (){ return data.begin (); }
		inline typename extended::vector<T>::normal_iterator end   (){ return data.end   (); }
		inline typename extended::vector<T>::normal_iterator rbegin(){ return data.rbegin(); }
		inline typename extended::vector<T>::normal_iterator rend  (){ return data.rend  (); }

		inline typename extended::vector<T>::const_iterator begin () const { return data.begin (); }
		inline typename extended::vector<T>::const_iterator end   () const { return data.end   (); }
		inline typename extended::vector<T>::const_iterator rbegin() const { return data.rbegin(); }
		inline typename extended::vector<T>::const_iterator rend  () const { return data.rend  (); }

	};

}