/**************************************************************************************************
 * Title:         Color.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "numerical_types.h"
#include "vector4.h"

namespace evansbros { namespace graphics {

    struct Color {

    public:
        Color() = default;

        Color(real white);
        Color(real white, real alpha);
        Color(real red, real green, real blue);
        Color(real red, real green, real blue, real alpha);

        real & red();
        real red() const;

        real & green();
        real green() const;

        real & blue();
        real blue() const;

        real & alpha();
        real alpha() const;

    private:
        math::vector4 components;
    };

} }
