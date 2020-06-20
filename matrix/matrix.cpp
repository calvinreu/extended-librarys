#include "matrix.h"

template<typename T>
extended::matrix<T>::matrix(const std::initializer_list<std::initializer_list<T>> initData) : data(initData.size()*initData.begin()->size()), rowSize(initData.begin()->size())
{

    for(auto iRow = initData.begin(); iRow < initData.end(); iRow++)
        for (auto i = iRow->begin(); i < iRow->end(); i++)
            data.push(*i);
    
}

template<typename T>
void extended::matrix<T>::operator=(const std::initializer_list<std::initializer_list<T>> initData)
{
    data.free_memory(data.max_size());
    data.add_memory(initData.size()*initData.begin()->size());

    for(auto iRow = initData.begin(); iRow < initData.end(); iRow++)
        for (auto i = iRow->begin(); i < iRow->end(); i++)
            data.push(*i);
    
    rowSize = initData.begin()->size();
}

template<typename T>
extended::matrix<T> extended::matrix<T>::operator+(const extended::matrix<T> &other) const
{
    if(data.size() != other.data.size() || rowSize != other.rowSize)
        throw std::runtime_error("diffrent ammount initialized or different size");

    extended::matrix<T> retVal(this->row_count(), this->row_size());

    for (size_t i = 0; i < data.size(); i++)
        retVal[i] = (*this)[i] + other[i];

    return std::move(retVal);
}

template<typename T>
extended::matrix<T> extended::matrix<T>::operator-(const extended::matrix<T> &other) const
{
    if(data.size() != other.data.size() || rowSize != other.rowSize)
        throw std::runtime_error("diffrent ammount initialized or different size");

    extended::matrix<T> retVal(this->row_count(), this->row_size());

    for (size_t i = 0; i < data.size(); i++)
        retVal[i] = (*this)[i] - other[i];

    return std::move(retVal);
}

template<typename T>
extended::matrix<T> extended::matrix<T>::operator*(const extended::matrix<T> & other) const
{
    if(this->rowSize != other.row_count())
        throw std::runtime_error("cannot multiply: this rowSize!= other rowCount");

    extended::matrix<T> retVal(other.rowSize, other.rowSize);

    T vectorMultiplicationResult;

    for (size_t iRow = 0; iRow < row_count(); iRow++)
    {
        for(size_t iColumn = 0; iColumn < other.rowSize; iColumn++)
        {
            vectorMultiplicationResult = 0;

            for(size_t i = 0; i < rowSize; i++)
                vectorMultiplicationResult += (*this)(iRow, i) * other(i, iColumn);

            retVal.data.push(vectorMultiplicationResult);
        }
    }
    return std::move(retVal);
}

template<typename T>
extended::matrix<T> extended::matrix<T>::operator*(const T &scalar) const
{
    extended::matrix<T> retVal = (*this);

    for(auto i = retVal.data.begin(); i < retVal.data.end(); i++)
        *i *= scalar;

        std::move(retVal);
}

template<typename T>
template<typename to>
extended::matrix<to> extended::matrix<T>::cast() const
{
    extended::matrix<to> retVal(this->size());

    for (auto i = data.begin(); i < data.end(); i++)
        retVal.data.push(static_cast<to>(*i));
    
    return std::move(retVal);
}

template<typename T>
void extended::matrix<T>::resize(const size_t &rowCount, const size_t &_rowSize)
{
    data.free_memory(data.max_size());
    data.add_memory(rowCount*_rowSize);
    rowSize = _rowSize;
}