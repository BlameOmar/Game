/**************************************************************************************************
 * Title:         OpenGL_Shader.cpp
 * Author:        Omar Stefan Evans
 * Created on:    <#Date#>
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "OpenGL_Shader.h"
#include <iostream>
#include <stdexcept>

namespace evansbros {
    namespace OpenGL {

        Shader::Shader(ShaderType type, string source) : _type(type)
        {
            const char *source_c_str = source.c_str();

            _id = glCreateShader((GLenum) type);
            glShaderSource(_id, 1, &source_c_str, NULL);
            glCompileShader(_id);

            GLint compiledSuccesfully = 0;
            GLint logLength = 0;

            glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                GLchar *log = new GLchar[logLength];
                glGetShaderInfoLog(_id, logLength, NULL, log);
                std::cerr << log << std::endl;
                delete [] log;
            }

            glGetShaderiv(_id, GL_COMPILE_STATUS, &compiledSuccesfully);
            if (compiledSuccesfully != GL_TRUE) {
                throw std::runtime_error("Shader did not compile");
            }
        }

        Shader::Shader(ShaderType type, Data data)
        : Shader(type, string((char *)data.getBytes(), data.getSize())) {}

        Shader::~Shader()
        {
            glDeleteShader(_id);
        }

        GLuint Shader::getID()
        {
            return _id;
        }

        ShaderType Shader::type() const
        {
            return _type;
        }

    }
}