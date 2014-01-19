/**************************************************************************************************
 * Title:         OpenGL_ShaderObject.cpp
 * Author:        Omar Stefan Evans
 * Created on:    <#Date#>
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "OpenGL_ShaderObject.h"
#include <iostream>
#include <stdexcept>

namespace evansbros {
    namespace OpenGL {

        ShaderObject::ShaderObject(ShaderType type, string source) : _type(type)
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

        ShaderObject::ShaderObject(ShaderObject && other)
        {
            this->_id = other._id;
            this->_type = other._type;

            other._id = 0;
        }

        ShaderObject::~ShaderObject()
        {
            glDeleteShader(_id);
        }

        GLuint ShaderObject::getID()
        {
            return _id;
        }

        ShaderType ShaderObject::type() const
        {
            return _type;
        }

    }
}