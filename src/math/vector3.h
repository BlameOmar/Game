/**************************************************************************************************
 * Title:         vector3.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-25
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "numerical_types.h"

namespace evansbros { namespace math {

    struct vector2;

    struct vector3 {
        real x = 0.0;
        real y = 0.0;
        real z = 0.0;

        /**
         * vector3()
         * Contructs a three-dimensional vector (x,y,z) with x,y,z = 0.0
         */
        vector3() = default;

        /**
         * vector3(real x, real y, real z)
         * Constructs a three-dimensional vector (x,y,z) with the given components
         * The third component (z) is optional; its default value is 0.0
         */
        vector3(real x, real y, real z = 0.0) : x(x), y(y), z(z) {}

        /**
         * Constructs a three-dimensional vector (x,y,z) given a two dimensional vector (x,y) and
         * a thrid component (z). The third component (z) is optional; its default value is 0.0
         */
        vector3(const vector2 & other, real z = 0.0);

        /**
         * (x,y,0) <- (x,y)
         */
        vector3 & operator=(const vector2 & other);

        /**
         * natural size()
         * Returns the size of the vector (always 3)
         */
        natural size() const { return 3; }

        /**
         * real * components()
         * Returns the array of components
         */
        real * components() { return (real *)this; }

        /**
         * Returns the array of components (const)
         */
        const real * components() const { return (real *)this; }

        real       * begin()        { return (real *)this; }
        real const * begin()  const { return (real *)this; }
        real const * cbegin() const { return (real *)this; }

        real       * end()          { return (real *)this + size(); }
        real const * end()    const { return (real *)this + size(); }
        real const * cend()   const { return (real *)this + size(); }

        real & operator()(natural i);
        real   operator()(natural i) const;

        real & operator[](natural i);
        real   operator[](natural i) const;

        vector3 & operator += (const vector3 & other);
        vector3 & operator -= (const vector3 & other);
        vector3 & operator *= (const real c);

        real _1_norm() const;
        real _2_norm() const;
        real p_norm(real p) const;
        real uniform_norm() const;

        real magnitude() const  { return _2_norm(); }
    };

    vector3 operator + (const vector3 & u, const vector3 & v);
    vector3 operator - (const vector3 & u, const vector3 & v);
    vector3 operator * (const real c, const vector3 & v);
    inline vector3 operator - (const vector3 & v) { return -1.0 * v; }
    inline vector3 operator * (const vector3 & v, const real c) { return c * v; }
    inline vector3 operator / (const vector3 & v, const real c) { return 1.0f / c * v; }

} }
