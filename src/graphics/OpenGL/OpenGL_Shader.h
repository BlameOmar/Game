/**************************************************************************************************
 * Title:         OpenGL_Shader.h
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

        class Shader {
        public:
            Shader(ShaderType type, string source);
            Shader(ShaderType type, Data data);
            Shader(const Shader & other) = delete;
            ~Shader();

            ShaderType type() const;
            GLuint getID();
        private:
            GLuint _id;
            ShaderType _type;

            friend class ShaderProgram;
        };

    }
}