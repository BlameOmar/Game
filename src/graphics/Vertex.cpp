/**************************************************************************************************
 * Title:         Vector.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-03
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "Vertex.h"

namespace evansbros { namespace graphics {

    Vertex::Vertex(vector3 position, Color color) : position(position), color(color)
    {
        /* Intentionally left blank */
    }

} }

#include <type_traits>

static_assert(std::is_standard_layout<evansbros::graphics::Vertex>::value,
              "evansbros::graphics::Vertex is not a standard layout type");

static_assert(std::is_trivially_copyable<evansbros::graphics::Vertex>::value,
              "evansbros::graphics::Vertex is not trivially copyable");