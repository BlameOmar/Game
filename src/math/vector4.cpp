/**************************************************************************************************
 * Title:         vector4.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-25
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "vector4.h"
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

    vector4::vector4(const vector2 & other, real z, real w) : x(other.x), y(other.y), z(z), w(w) {}

    vector4::vector4(const vector3 & other, real w) : x(other.x), y(other.y), z(other.z), w(w) {}

    real & vector4::operator()(natural i)
    {
        if (i >= size()) {
            throw std::domain_error("Argument not in [0, size())");
        }
        return components()[i];
    }

    real vector4::operator()(natural i) const
    {
        if (i >= size()) {
            throw std::domain_error("Argument not in [0, size())");
        }
        return components()[i];
    }

    real & vector4::operator[](natural i)
    {
        if (i >= size()) {
            throw std::out_of_range("index >= size()");
        }
        return components()[i];
    }

    real vector4::operator[](natural i) const
    {
        if (i >= size()) {
            throw std::out_of_range("index >= size()");
        }
        return components()[i];
    }

    vector4 & vector4::operator=(const vector2 & other)
    {
        x = other.x;
        y = other.y;
        z = 0.0;
        w = 0.0;

        return *this;
    }

    vector4 & vector4::operator=(const vector3 & other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = 0.0;

        return *this;
    }

    vector4 & vector4::operator += (const vector4 & other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;

        return *this;
    }

    vector4 & vector4::operator -= (const vector4 & other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;

        return *this;
    }

    vector4 & vector4::operator *= (const real c)
    {
        x *= c;
        y *= c;
        z *= c;
        w *= c;

        return *this;
    }

    real vector4::_1_norm() const
    {
        return abs(x) + abs(y) + abs(z) + abs(w);
    }

    real vector4::_2_norm() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    real vector4::p_norm(real p) const
    {
        return pow((abs(pow(x, p)) + abs(pow(y, p)) + abs(pow(z, p)) + abs(pow(w, p))), 1.0 / p);
    }

    real vector4::uniform_norm() const
    {
        return max(abs(x), max(abs(y), max(abs(z), abs(w))));
    }

    vector4 operator + (const vector4 & u, const vector4 & v)
    {
        return vector4(u) += v;
    }

    vector4 operator - (const vector4 & u, const vector4 & v)
    {
        return vector4(u) -= v;
    }

    vector4 operator * (const real c, const vector4 & v)
    {
        return vector4(v) *= c;
    }
    
} }

#include <type_traits>

static_assert(sizeof(evansbros::math::vector4) == 16,
              "sizeof(evansbros::math::vector4) != 16 bytes");

static_assert(std::is_standard_layout<evansbros::math::vector4>::value,
              "evansbros::math::vector4 is not a standard layout type");

static_assert(std::is_trivially_copyable<evansbros::math::vector4>::value,
              "evansbros::math::vector4 is not trivially copyable");
