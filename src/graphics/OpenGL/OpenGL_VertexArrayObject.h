/**************************************************************************************************
 * Title:         OpenGL_VertexArrayObject.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-19
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "OpenGL.h"

namespace evansbros {
    namespace OpenGL {

        class VertexArrayObject{
        public:
            VertexArrayObject();
            VertexArrayObject(const VertexArrayObject & other) = delete;
            ~VertexArrayObject();

            void bindToVertexArray();
        private:
            GLuint vertexArrayObjectID = 0;
        };
        
    }
}