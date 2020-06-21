#include "matrix.h"

template<typename T>
extended::matrix<T>::matrix(const size_t &rowCount, const size_t &rowSize) : data(rowCount)
{
    for(size_t i = 0; i < data.max_size(); i++)
        data.push(rowSize);
}

template<typename T>
extended::matrix<T>::matrix(const std::initializer_list<std::initializer_list<T>> &initData) : data(initData.size())
{
    for(auto iRow = initData.begin(); iRow < initData.end(); iRow++)
    {
        data.push(initData.begin()->size());
        for (auto i = iRow->begin(); i < iRow->end(); i++)
            data.last().push(*i);
    }
}

template<typename T>
extended::matrix<T> extended::matrix<T>::operator+(const extended::matrix<T> &other) const
{
    if(this->row_count() != other.row_count() || this->row_size() != other.row_size())
        throw std::runtime_error("diffrent ammount initialized or different size");

    extended::matrix<T> retVal(this->row_count(), this->row_size());

    for (size_t iRow = 0; iRow < row_count(); iRow++)
        for(size_t i= 0; i < this->row_size(); i++)
            retVal(iRow, i) = (*this)(iRow, i) + other(iRow, i);

    return std::move(retVal);
}

template<typename T>
extended::matrix<T> extended::matrix<T>::operator-(const extended::matrix<T> &other) const
{
    if(data.size() != other.data.size() || this->row_size() != other.row_size())
        throw std::runtime_error("diffrent ammount initialized or different size");

    extended::matrix<T> retVal(this->row_count(), this->row_size());

    for (size_t iRow = 0; iRow < row_count(); iRow++)
        for(size_t i = 0; i < this->row_size(); i++)
            retVal(iRow, i) = (*this)(iRow, i) - other(iRow, i);

    return std::move(retVal);
}

template<typename T>
extended::matrix<T> extended::matrix<T>::operator*(const extended::matrix<T> & other) const
{
    if(this->row_size() != other.row_count())
        throw std::runtime_error("cannot multiply: this rowSize!= other rowCount");

    extended::matrix<T> retVal(this->row_count(), other.row_size());

    T vectorMultiplicationResult;

    for (size_t iRow = 0; iRow < row_count(); iRow++)
    {
        for(size_t iColumn = 0; iColumn < other.row_size(); iColumn++)
        {
            vectorMultiplicationResult = 0;

            for(size_t i = 0; i < row_size(); i++)
                vectorMultiplicationResult += (*this)(iRow, i) * other(i, iColumn);

            retVal.data[iRow].push(vectorMultiplicationResult);
        }
    }
    return std::move(retVal);
}

template<typename T>
extended::matrix<T> extended::matrix<T>::operator*(const T &scalar) const
{
    extended::matrix<T> retVal = (*this);

    for(auto iRow = retVal.data.begin(); iRow < retVal.data.end(); iRow++)
        for(auto i = iRow->begin(); i < iRow->end(); i++)
            *i *= scalar;

    std::move(retVal);
}

template<typename T>
template<typename to>
extended::matrix<to> extended::matrix<T>::cast() const
{
    extended::matrix<to> retVal(this->size());

    for (auto iRow = data.begin(); iRow < data.end(); iRow++)
        for(auto i = iRow->begin(); i < iRow->end(); i++)
            iRow->push(static_cast<to>(*i));
    
    return std::move(retVal);
}

template<typename T>
void extended::matrix<T>::recreate(const size_t &rowCount, const size_t &rowSize)
{
    data.free_memory(data.max_size());//also destructs every row
    data.add_memory(rowCount);
    
    for(size_t i = 0; i < data.max_size(); i++)
        data.push(rowSize);
}