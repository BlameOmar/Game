/**************************************************************************************************
 * Title:         Vertex.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-03
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "vector3.h"
#include "Color.h"

namespace evansbros { namespace graphics {

    using math::vector3;

    struct Vertex {
        vector3 position;
        Color color;

        Vertex() = default;
        Vertex(vector3 position, Color color);
    };

} }