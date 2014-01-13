/**************************************************************************************************
 * Title:         abstract_vector.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-24
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "numerical_types.h"

namespace evansbros { namespace math {
    class abstract_vector {
    public:

        real & operator()(natural i);
        real   operator()(natural i) const;

        real & operator[](natural i);
        real   operator[](natural i) const;

        real * begin();
        real const * begin() const;
        real const * cbegin() const;

        real * end();
        real const * end() const;
        real const * cend() const;

        /**
         * Returns the size of the vector
         */
        virtual natural size() const  = 0;

        /**
         * Returns a pointer to the components of the vector
         */
        virtual real * components()  = 0;

        /**
         * Returns a pointer to the components (const) of the vector
         */
        virtual real const * components() const  = 0;

        real get1Norm() const;
        real get2Norm() const;
        real getUniformNorm() const;
        real getPNorm(real p) const;
        real getMagnitude() const  { return get2Norm(); }

    protected:
        /**
         * Adds the vector pointed to by v to the vector pointed to by u
         */
        static void add_to(abstract_vector * u, const abstract_vector * v);

        /**
         * Subtracts the vector pointed to by v from the vector pointed to by u
         */
        static void subtract_from(abstract_vector * u, const abstract_vector * v);

        /**
         * Scales the vector pointed to by u by c
         */
        static void scale_by(abstract_vector * u, const real c);

        /**
         * Negate the vector pointed to by u
         */
        static void negate(abstract_vector * u);

    };
} }
