/**************************************************************************************************
 * Title:         vector2.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-25
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "vector2.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

using std::abs;
using std::max;
using std::pow;
using std::sqrt;

namespace evansbros { namespace math {

    real & vector2::operator()(natural i)
    {
        if (i >= size()) {
            throw std::domain_error("Argument not in [0, size())");
        }
        return components()[i];
    }

    real vector2::operator()(natural i) const
    {
        if (i >= size()) {
            throw std::domain_error("Argument not in [0, size())");
        }
        return components()[i];
    }

    real & vector2::operator[](natural i)
    {
        if (i >= size()) {
            throw std::out_of_range("index >= size()");
        }
        return components()[i];
    }

    real vector2::operator[](natural i) const
    {
        if (i >= size()) {
            throw std::out_of_range("index >= size()");
        }
        return components()[i];
    }

    vector2 & vector2::operator += (const vector2 & other)
    {
        x += other.x;
        y += other.y;

        return *this;
    }

    vector2 & vector2::operator -= (const vector2 & other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    vector2 & vector2::operator *= (const real c)
    {
        x *= c;
        y *= c;

        return *this;
    }

    real vector2::_1_norm() const
    {
        return abs(x) + abs(y);
    }

    real vector2::_2_norm() const
    {
        return sqrt(x * x + y * y);
    }

    real vector2::p_norm(real p) const
    {
        return pow((abs(pow(x, p)) + abs(pow(y, p))), 1.0 / p);
    }

    real vector2::uniform_norm() const
    {
        return max(abs(x), abs(y));
    }

    vector2 operator + (const vector2 & u, const vector2 & v)
    {
        return vector2(u) += v;
    }

    vector2 operator - (const vector2 & u, const vector2 & v)
    {
        return vector2(u) -= v;
    }

    vector2 operator * (const real c, const vector2 & v)
    {
        return vector2(v) *= c;
    }

} }

#include <type_traits>

static_assert(sizeof(evansbros::math::vector2) == 8,
              "sizeof(evansbros::math::vector2) != 8 bytes");

static_assert(std::is_standard_layout<evansbros::math::vector2>::value,
              "evansbros::math::vector2 is not a standard layout type");

static_assert(std::is_trivially_copyable<evansbros::math::vector2>::value,
              "evansbros::math::vector2 is not trivially copyable");
