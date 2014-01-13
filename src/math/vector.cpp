/**************************************************************************************************
 * Title:         vector.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-07-06
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: None
 **************************************************************************************************/

#include "vector.h"

#include <cmath>
#include <algorithm>

namespace evansbros { namespace math {

    vector::vector(std::initializer_list<real> values) : _size((natural)values.size()) {
        _components = new real[_size];
        std::copy(values.begin(), values.end(), _components);
    }

    vector& vector::add(const vector& other) {
        abstract_vector::add_to(this, &other);

        return *this;
    }

    vector& vector::subtract(const vector& other) {
        abstract_vector::subtract_from(this, &other);

        return *this;
    }

    vector& vector::scale(const real c) {
        abstract_vector::scale_by(this, c);

        return *this;
    }

    vector add(const vector& u, const vector& v) {
        return vector(u).add(v);
    }

    vector subtract(const vector& u, const vector& v) {
        return vector(u).subtract(v);
    }
    
    vector scale(const vector& v, const real c) {
        return vector(v).scale(c);
    }
    
    vector operator + (const vector& u, const vector& v) {
        return add(u, v);
    }
    
    vector operator - (const vector& u, const vector& v) {
        return subtract(u, v);
    }
    
    vector operator * (const vector& v, const real c) {
        return scale(v, c);
    }

} }
