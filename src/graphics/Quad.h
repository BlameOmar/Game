/**************************************************************************************************
 * Title:         Quad.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "Vertex.h"

namespace evansbros { namespace graphics {

    struct Quad {
        Vertex v1;
        Vertex v2;
        Vertex v3;
        Vertex v4;

        Quad() = delete;
        Quad(Vertex v1, Vertex v2, Vertex v3, Vertex v4);

        static const Quad COLORLESS_UNIT_SQUARE;
        static const Quad COLORLESS_CENTERED_UNIT_SQUARE;
    };

} }
