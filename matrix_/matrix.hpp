#pragma once
#include <vector>
#include <initializer_list>

using std::vector;

namespace extended{
    template<typename T>
    class matrix
    {
    private:
        std::vector<T> data;
        std::vector<size_t> size;//size.len = dimensions

        //optimization
		template<typename t = T>
		inline typename std::enable_if<!std::is_trivially_copy_constructible<t>::value>::type
			copy(const T* source, T* destination, const size_t &size) { memcpy(destination, source, size*sizeof(T)); }

		template<typename t = T>
		inline typename std::enable_if<std::is_trivially_copy_constructible<t>::value>::type
			copy(const T* source, T* destination, const size_t &size){
				for (size_t i = 0; i < size; i++)
					new(destination + i) T(source[i]);

    public:
    
        matrix();
        matrix(const size_t &rowCount, const size_t &colCount);
        matrix(const size_t &rowCount, const size_t &colCount, const std::initializer_list<T> &initData);
        matrix(const std::initializer_list<size_t> &size);
        matrix(const std::vector &size);
        matrix(matrix<T> && other);

        ~matrix();
    };
}