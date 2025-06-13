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

/*!
 * \class Array2D
 * \brief Use to manage a 2-dimensional array
 */
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

/*!
 * \brief Construct a 2D array
 * at specified size
 *
 * \param[in] nbRows
 * Number of rows.
 * \param[in] nbCols
 * Number of colums
 */
template<typename T>
Array2D<T>::Array2D(size_t nbRows, size_t nbCols)
{
    resize(m_rows, m_cols);
}

/*!
 * \brief Construct an empty 2D array
 */
template<typename T>
Array2D<T>::Array2D()
    : m_rows(0), m_cols(0)
{
    /* Nothing to do */
}

/*!
 * \brief Get number of rows
 *
 * \return
 * Returns number of rows available
 *
 * \sa getCols(), getSize()
 */
template<typename T>
size_t Array2D<T>::getRows() const
{
    return m_rows;
}

/*!
 * \brief Get number of columns
 *
 * \return
 * Returns number of columns available
 *
 * \sa getRows(), getSize()
 */
template<typename T>
size_t Array2D<T>::getCols() const
{
    return m_cols;
}

/*!
 * \brief Get total size of 2D array (a.k.a number
 * of elements)
 *
 * \return
 * Returns number of elements
 *
 * \sa getRows(), getCols()
 */
template<typename T>
size_t Array2D<T>::getSize() const
{
    return m_rows * m_cols;
}

/*!
 * \brief Clear content of 2D array
 * \details
 * Size will be reset to \c 0 and all elements will
 * be removed
 *
 * \note
 * This method doesn't impact internal capacity of
 * the array, see \c resize() method for more details.
 *
 * \sa resize()
 */
template<typename T>
void Array2D<T>::clear()
{
    m_rows = 0;
    m_cols = 0;
    m_data.clear();
}

/*!
 * \brief Resize array to specified size
 *
 * \param[in] nbRows
 * Number of rows.
 * \param[in] nbCols
 * Number of colums
 *
 * \note
 * This method will only extend \b capacity of the 2D array,
 * no shrink operation will be performed.
 */
template<typename T>
void Array2D<T>::resize(size_t nbRows, size_t nbCols)
{
    m_rows = nbRows;
    m_cols = nbCols;
    m_data.resize(m_rows * m_cols);
}

/*!
 * \brief Use to insert a value at specified
 * indexes.
 *
 * \param[in] row
 * Row index to use. \n
 * Must be valid (i.e <tt>0 <= row < getRows()</tt>).
 * \param[in] col
 * Column index to use. \n
 * Must be valid (i.e <tt>0 <= col < getCols()</tt>).
 * \param[in] value
 * Value to insert
 */
template<typename T>
void Array2D<T>::insert(size_t row, size_t col, const T &value)
{
    (*this)(row, col) = value;
}

/*!
 * \brief Get modifiable reference to an element
 *
 * \param[in] row
 * Row index to use. \n
 * Must be valid (i.e <tt>0 <= row < getRows()</tt>).
 * \param[in] col
 * Column index to use. \n
 * Must be valid (i.e <tt>0 <= col < getCols()</tt>).
 *
 * \return
 * Returns modifiable reference to an element
 */
template<typename T>
T& Array2D<T>::operator()(size_t row, size_t col)
{
    return m_data[row * m_cols + col];
}

/*!
 * \brief Get constant reference to an element
 *
 * \param[in] row
 * Row index to use. \n
 * Must be valid (i.e <tt>0 <= row < getRows()</tt>).
 * \param[in] col
 * Column index to use. \n
 * Must be valid (i.e <tt>0 <= col < getCols()</tt>).
 *
 * \return
 * Returns constant reference to an element
 */
template<typename T>
const T& Array2D<T>::operator()(size_t row, size_t col) const
{
    return m_data[row * m_cols + col];
}

} // namespace tbq

#endif // TBQ_CONTAINER_ARRAY2D_H
