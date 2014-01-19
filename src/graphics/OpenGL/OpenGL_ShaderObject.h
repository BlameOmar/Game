/**************************************************************************************************
 * Title:         OpenGL_ShaderObject.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-19
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "OpenGL.h"
#include "types.h"
#include "Data.h"

namespace evansbros {
    namespace OpenGL {

        enum class ShaderType : GLenum {
            VERTEX_SHADER       = GL_VERTEX_SHADER,
            FRAGMENT_SHADER     = GL_FRAGMENT_SHADER,
            GEOMETRY_SHADER     = GL_GEOMETRY_SHADER
        };

        class ShaderObject {
        public:
            ShaderObject(ShaderType type, string source);
            ShaderObject(ShaderType type, Data data);
            ShaderObject(const ShaderObject & other) = delete;
            ShaderObject(ShaderObject && other);
            ~ShaderObject();

            ShaderType type() const;
            GLuint getID();
        private:
            GLuint _id;
            ShaderType _type;

            friend class ShaderProgram;
        };

    }
}