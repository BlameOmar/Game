/**************************************************************************************************
 * Title:         matrix.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-24
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include <stdexcept>

#include "numerical_types.h"

namespace evansbros { namespace math {

    class matrix {
        natural_16bit rows          = 0;
        natural_16bit columns       = 0;
        real          *data         = nullptr;
    public:
        matrix() = default;

        matrix(natural_16bit n);
        matrix(natural_16bit rows, natural_16bit columns);

        matrix(matrix && other);
        matrix(const matrix & other);

        matrix& operator=(matrix && other);
        matrix& operator=(const matrix & other);

        ~matrix();

        static matrix identity(natural_16bit n);

        matrix& operator+=(const matrix & other) throw(std::domain_error);
        matrix& operator*=(real c);

        friend matrix operator+(const matrix & A, const matrix & B) throw(std::domain_error);

        friend matrix operator*(const matrix & A, real c);
        friend matrix operator*(real c, const matrix & A);

        friend matrix transpose(const matrix & A);

        real & operator() (natural i, natural j) throw(std::domain_error);
        real   operator() (natural i, natural j) const throw(std::domain_error);

        const real * getData() const;
        natural_16bit getRows() const;
        natural_16bit getColumns() const;
    private:
        void movePrivateData(matrix & other);
        void copyPrivateData(const matrix & other);
    };

} }
