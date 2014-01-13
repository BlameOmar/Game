/**************************************************************************************************
 * Title:         Quad.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "Quad.h"

namespace evansbros { namespace graphics {

    Quad::Quad(Vertex v1, Vertex v2, Vertex v3, Vertex v4) : v1(v1), v2(v2), v3(v3), v4(v4)
    {
        /* Intentionally Left Blank */
    }

} }

#include <type_traits>

static_assert(std::is_standard_layout<evansbros::graphics::Quad>::value,
              "evansbros::graphics::Quad is not a standard layout type");

static_assert(std::is_trivially_copyable<evansbros::graphics::Quad>::value,
              "evansbros::graphics::Quad is not trivially copyable");