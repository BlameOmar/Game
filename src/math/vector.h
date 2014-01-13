/**************************************************************************************************
 * Title:         vector.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-07-06
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: None
 **************************************************************************************************/

#pragma once

#include "abstract_vector.h"

#include <initializer_list>

namespace evansbros { namespace math {

    class vector : public abstract_vector {
        natural _size = 0;
        real * _components = nullptr;
    public:
        vector() = default;
        vector(std::initializer_list<real>);
        vector(const vector & original);

        natural size() const { return _size; }
        real * components() { return _components; }
        real const * components() const { return _components; }

        vector& add(const vector& other);
        vector& subtract(const vector& other);
        vector& scale(const real c);

        vector& operator += (const vector& other) { return add(other); }
        vector& operator -= (const vector& other) { return subtract(other); }
        vector& operator *= (const real c) { return scale(c); }

        friend vector add(const vector& u, const vector& v);
        friend vector subtract(const vector& u, const vector& v);
        friend vector scale (const vector& v, const real c);

        friend vector operator + (const vector& u, const vector& v);
        friend vector operator - (const vector& u, const vector& v);
        friend vector operator * (const vector& v, const real c);
        friend vector operator * (const real c, const vector& v) { return v * c; }
        friend vector operator / (const vector& v, const real c) { return v * (1.0f / c); }
    };

} }
