/**************************************************************************************************
 * Title:         Color.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "Color.h"

namespace evansbros { namespace graphics {

    Color::Color(real white) : Color(white, 1.0)
    {
        /* Intentionally Left Blank */
    }

    Color::Color(real white, real alpha) : Color(white, white, white, alpha)
    {
        /* Intentionally Left Blank */
    }

    Color::Color(real red, real green, real blue) : Color(red, green, blue, 1.0)
    {
        /* Intentionally Left Blank */
    }

    Color::Color(real red, real green, real blue, real alpha) : components{red, green, blue, alpha}
    {
        /* Intentionally Left Blank */
    }

    real & Color::red()
    {
        return components[0];
    }

    real Color::red() const
    {
        return components[0];
    }

    real & Color::green()
    {
        return components[1];
    }

    real Color::green() const
    {
        return components[1];
    }

    real & Color::blue()
    {
        return components[2];
    }

    real Color::blue() const
    {
        return components[2];
    }

    real & Color::alpha()
    {
        return components[3];
    }

    real Color::alpha() const
    {
        return components[3];
    }
    
} }

#include <type_traits>

static_assert(std::is_standard_layout<evansbros::graphics::Color>::value,
              "evansbros::graphics::Color is not a standard layout type");

static_assert(std::is_trivially_copyable<evansbros::graphics::Color>::value,
              "evansbros::graphics::Color is not trivially copyable");
