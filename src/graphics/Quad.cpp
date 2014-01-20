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

    const Quad Quad::COLORLESS_UNIT_SQUARE({{0.0, 0.0}, Color()},
                               {{1.0, 0.0}, Color()},
                               {{1.0, 1.0}, Color()},
                               {{0.0, 1.0}, Color()});

    const Quad Quad::COLORLESS_CENTERED_UNIT_SQUARE({{-0.5, -0.5}, Color()},
                                                    {{ 0.5, -0.5}, Color()},
                                                    {{ 0.5,  0.5}, Color()},
                                                    {{-0.5,  0.5}, Color()});
    
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