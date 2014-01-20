/**************************************************************************************************
 * Title:         OpenGL_VertexArrayObject.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-19
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "OpenGL_VertexArrayObject.h"

namespace evansbros {
    namespace OpenGL {

        VertexArrayObject::VertexArrayObject()
        {
            glGenVertexArrays(1, &vertexArrayObjectID);
        }

        VertexArrayObject::~VertexArrayObject()
        {
            glDeleteVertexArrays(1, &vertexArrayObjectID);
        }

        void VertexArrayObject::bindToVertexArray()
        {
            glBindVertexArray(vertexArrayObjectID);
        }

    }
}