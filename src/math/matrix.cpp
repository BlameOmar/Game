/**************************************************************************************************
 * Title:         matrix.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-24
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "matrix.h"
#include <cstring>
#include <sstream>

namespace evansbros { namespace math {

    matrix::matrix(natural_16bit n) : matrix(n, n)
    {
        /* Intentionally left blank */
    }

    matrix::matrix(natural_16bit rows, natural_16bit columns) : rows(rows), columns(columns)
    {
        if (rows * columns == 0) {
            this->rows = this->columns = 0;
            data = nullptr;
        } else {
            data = new real[rows * columns];
            std::memset(data, 0, sizeof(real) * rows * columns);
        }
    }

    matrix::matrix(matrix && other)
    {
        movePrivateData(other);
    }

    matrix::matrix(const matrix & other)
    {
        copyPrivateData(other);
    }

    matrix& matrix::operator=(matrix && other)
    {
        if (this != &other) {
            delete [] data;

            movePrivateData(other);
        }

        return *this;
    }

    matrix& matrix::operator=(const matrix & other)
    {
        if (this != &other) {
            delete [] data;

            copyPrivateData(other);
        }

        return *this;
    }

    matrix::~matrix()
    {
        delete [] data;
    }

    matrix matrix::identity(natural_16bit n)
    {
        matrix M(n);

        for (natural_16bit i = 0; i < n; ++i) {
            M(i,i) = 1.0;
        }

        return M;
    }

    real & matrix::operator() (natural i, natural j) throw(std::domain_error)
    {
        if (i >= rows || j >= columns) {
            std::ostringstream out;
            out << "(" << i << ", " << j << ") is not in the domain: "
                << "[0, " << rows << ") X [0, " << columns << ")\n";
            throw (std::domain_error(out.str()));
        }
        return data[i * columns + j];
    }

    real   matrix::operator() (natural i, natural j) const throw(std::domain_error)
    {
        if (i >= rows || j >= columns) {
            std::ostringstream out;
            out << "(" << i << ", " << j << ") is not in Domain = "
            << "[0, " << rows << ") X [0, " << columns << ")\n";
            throw (std::domain_error(out.str()));
        }
        return data[i * columns + j];
    }

    const real * matrix::getData() const
    {
        return data;
    }

    natural_16bit matrix::getRows() const
    {
        return rows;
    }

    natural_16bit matrix::getColumns() const
    {
        return columns;
    }

    void matrix::movePrivateData(matrix & other)
    {
        rows = other.rows;
        columns = other.columns;
        data = other.data;

        other.rows = 0;
        other.columns = 0;
        other.data = nullptr;
    }

    void matrix::copyPrivateData(const matrix & other)
    {
        rows = other.rows;
        columns = other.columns;

        if (rows * columns == 0) {
            data = nullptr;
        } else {
            data = new real[rows * columns];
            std::memcpy(data, other.data, sizeof(real) * rows * columns);
        }
    }

    matrix& matrix::operator+=(const matrix & other) throw(std::domain_error)
    {
        if (rows != other.rows || columns != other.columns) {
            throw std::domain_error("Addition is not defined on matricies of differeing size.");
        }

        for (int i = 0; i < rows * columns; ++i) {
            data[i] += other.data[i];
        }

        return *this;
    }

    matrix& matrix::operator*=(real c)
    {
        for (int i = 0; i < rows * columns; ++i) {
            data[i] *= c;
        }

        return *this;
    }

    matrix operator+(const matrix & A, const matrix & B) throw(std::domain_error)
    {
        return matrix(A) += B;
    }

    matrix operator*(const matrix & A, real c)
    {
        return matrix(A) *= c;
    }

    matrix operator*(real c, const matrix & A)
    {
        return A * c;
    }

    matrix transpose(const matrix & A)
    {
        matrix B(A.columns, A.rows);

        for (natural_16bit i = 0; i < B.rows; ++i) {
            for (natural_16bit j = 0; j < B.columns; ++j) {
                B(i,j) = A(j,i);
            }
        }

        return B;
    }

} }
