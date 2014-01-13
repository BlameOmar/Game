/**************************************************************************************************
 * Title:         vector4.h
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
    struct vector3;

    struct vector4 {
        real x = 0.0;
        real y = 0.0;
        real z = 0.0;
        real w = 0.0;

        /**
         * Contructs a three-dimensional vector (x,y,z) with x,y,z = 0.0
         */
        vector4() = default;

        /**
         * Constructs a four-dimensional vector (x,y,z,w) with the given components.
         * The third and fourth components (z, w) are optional; their default value is 0.0
         */
        vector4(real x, real y, real z = 0.0, real w = 0.0) : x(x), y(y), z(z), w(w) {}

        /**
         * Constructs a four-dimensional vector (x,y,z,w) given a two dimensional vector (x,y)
         * and, optionally, the third and fourth components (z and w), which default to 0.0.
         */
        vector4(const vector2 & other, real z = 0.0, real w = 0.0);

        /**
         * Constructs a four-dimensional vector (x,y,z,w) given a three dimensional vector (x,y,z)
         * and , optionally, the fourth component (w), which defaults to 0.0.
         */
        vector4(const vector3 & other, real w = 0.0);

        /**
         * (x,y,0,0) <- (x,y)
         */
        vector4 & operator=(const vector2 & other);

        /**
         * (x,y,z,0) <- (x,y,z)
         */
        vector4 & operator=(const vector3 & other);

        /**
         * Returns the size of the vector (always 4)
         */
        natural size() const { return 4; }

        /**
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

        vector4 & operator += (const vector4 & other);
        vector4 & operator -= (const vector4 & other);
        vector4 & operator *= (const real c);
        vector4 & operator - ();

        real _1_norm() const;
        real _2_norm() const;
        real p_norm(real p) const;
        real uniform_norm() const;

        real magnitude() const  { return _2_norm(); }
    };

    vector4 operator + (const vector4 & u, const vector4 & v);
    vector4 operator - (const vector4 & u, const vector4 & v);
    vector4 operator * (const real c, const vector4 & v);
    inline vector4 operator - (const vector4 & v) { return -1.0 * v; }
    inline vector4 operator * (const vector4 & v, const real c) { return c * v; }
    inline vector4 operator / (const vector4 & v, const real c) { return 1.0f / c * v; }

} }
