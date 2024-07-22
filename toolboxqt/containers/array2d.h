#ifndef TBQ_CONTAINER_ARRAY2D_H
#define TBQ_CONTAINER_ARRAY2D_H

#include "toolboxqt/toolboxqt_global.h"
#include <QVector>

/*****************************/
/* Start namespace           */
/*****************************/

namespace tbq
{

/*****************************/
/* Define template interface */
/*****************************/
template <typename T>
class TOOLBOXQT_EXPORT Array2D
{

public:
    explicit Array2D();
    explicit Array2D(size_t nbRows, size_t nbCols);

public:
    size_t getRows() const;
    size_t getCols() const;
    size_t getSize() const;

public:
    void clear();
    void resize(size_t nbRows, size_t nbCols);

    void insert(size_t row, size_t col, const T &value);

public:
    T& operator()(size_t row, size_t col);
    const T& operator()(size_t row, size_t col) const;

public: // Friends operator defined using "Making new friends" idiom (https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Making_New_Friends)
    friend bool operator==(const Array2D<T> &left, const Array2D<T> &right)
    {
        return left.m_rows == right.m_rows
            && left.m_cols == right.m_cols
            && left.m_data == right.m_data;
    }

    friend bool operator!=(const Array2D<T> &left, const Array2D<T> &right)
    {
        return !(left == right);
    }

private:
    size_t m_rows;
    size_t m_cols;
    QVector<T> m_data;
};

/*****************************/
/* Define template
 *      implementation       */
/*****************************/

template<typename T>
Array2D<T>::Array2D(size_t nbRows, size_t nbCols)
{
    resize(m_rows, m_cols);
}

template<typename T>
Array2D<T>::Array2D()
    : m_rows(0), m_cols(0)
{
    /* Nothing to do */
}

template<typename T>
size_t Array2D<T>::getRows() const
{
    return m_rows;
}

template<typename T>
size_t Array2D<T>::getCols() const
{
    return m_cols;
}

template<typename T>
size_t Array2D<T>::getSize() const
{
    return m_rows * m_cols;
}

template<typename T>
void Array2D<T>::clear()
{
    m_rows = 0;
    m_cols = 0;
    m_data.clear();
}

template<typename T>
void Array2D<T>::resize(size_t nbRows, size_t nbCols)
{
    m_rows = nbRows;
    m_cols = nbCols;
    m_data.resize(m_rows * m_cols);
}

template<typename T>
void Array2D<T>::insert(size_t row, size_t col, const T &value)
{
    (*this)(row, col) = value;
}

template<typename T>
T& Array2D<T>::operator()(size_t row, size_t col)
{
    return m_data[row * m_cols + col];
}

template<typename T>
const T& Array2D<T>::operator()(size_t row, size_t col) const
{
    return m_data[row * m_cols + col];
}

} // namespace tbq

#endif // TBQ_CONTAINER_ARRAY2D_H
