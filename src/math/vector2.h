/**************************************************************************************************
 * Title:         vector2.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-25
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "numerical_types.h"

namespace evansbros { namespace math {

    struct vector2 {
        real x = 0.0;
        real y = 0.0;

        /**
         * Contructs a two-dimensional vector (x,y) with x,y = 0.0
         */
        vector2() = default;

        /**
         * Constructs a two-dimensional vector (x,y) with the given components
         */
        vector2(real x, real y) : x(), y(y) {}

        /**
         * Returns the size of the vector (always 2)
         */
        natural size() const { return 2; }

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

        vector2 & operator += (const vector2 & other);
        vector2 & operator -= (const vector2 & other);
        vector2 & operator *= (const real c);

        real _1_norm() const;
        real _2_norm() const;
        real p_norm(real p) const;
        real uniform_norm() const;

        real magnitude() const  { return _2_norm(); }
    };

    vector2 operator + (const vector2 & u, const vector2 & v);
    vector2 operator - (const vector2 & u, const vector2 & v);
    vector2 operator * (const real c, const vector2 & v);
    inline vector2 operator - (const vector2 & v) { return -1.0 * v; };
    inline vector2 operator * (const vector2 & v, const real c) { return c * v; }
    inline vector2 operator / (const vector2 & v, const real c) { return 1.0f / c * v; }
} }
