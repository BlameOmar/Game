/**************************************************************************************************
 * Title:         vector3.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-25
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "vector3.h"
#include "vector2.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

using std::abs;
using std::max;
using std::pow;
using std::sqrt;

namespace evansbros { namespace math {

    vector3::vector3(const vector2 & other, real z) : x(other.x), y(other.y), z(z) {}

    real & vector3::operator()(natural i)
    {
        if (i >= size()) {
            throw std::domain_error("Argument not in [0, size())");
        }
        return components()[i];
    }

    real vector3::operator()(natural i) const
    {
        if (i >= size()) {
            throw std::domain_error("Argument not in [0, size())");
        }
        return components()[i];
    }

    real & vector3::operator[](natural i)
    {
        if (i >= size()) {
            throw std::out_of_range("index >= size()");
        }
        return components()[i];
    }

    real vector3::operator[](natural i) const
    {
        if (i >= size()) {
            throw std::out_of_range("index >= size()");
        }
        return components()[i];
    }

    vector3 & vector3::operator=(const vector2 & other)
    {
        x = other.x;
        y = other.y;
        z = 0.0;

        return *this;
    }

    vector3 & vector3::operator += (const vector3 & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    vector3 & vector3::operator -= (const vector3 & other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

    vector3 & vector3::operator *= (const real c)
    {
        x *= c;
        y *= c;
        z *= c;

        return *this;
    }

    real vector3::_1_norm() const
    {
        return abs(x) + abs(y) + abs(z);
    }

    real vector3::_2_norm() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    real vector3::p_norm(real p) const
    {
        return pow((abs(pow(x, p)) + abs(pow(y, p)) + abs(pow(z, p))), 1.0 / p);
    }

    real vector3::uniform_norm() const
    {
        return max(abs(x), max(abs(y), abs(z)));
    }

    vector3 operator + (const vector3 & u, const vector3 & v)
    {
        return vector3(u) += v;
    }

    vector3 operator - (const vector3 & u, const vector3 & v)
    {
        return vector3(u) -= v;
    }

    vector3 operator * (const real c, const vector3 & v)
    {
        return vector3(v) *= c;
    }

} }

#include <type_traits>

static_assert(sizeof(evansbros::math::vector3) == 12,
              "sizeof(evansbros::math::vector3) != 12 bytes");

static_assert(std::is_standard_layout<evansbros::math::vector3>::value,
              "evansbros::math::vector3 is not a standard layout type");

static_assert(std::is_trivially_copyable<evansbros::math::vector3>::value,
              "evansbros::math::vector3 is not trivially copyable");
