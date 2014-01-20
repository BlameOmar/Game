/**************************************************************************************************
 * Title:         OpenGL_ShaderProgram.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-19
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "OpenGL_ShaderProgram.h"
#include <iostream>
#include <stdexcept>

namespace evansbros {
    namespace OpenGL {
        ShaderProgram::ShaderProgram(std::initializer_list<Shader *> shaders)
        {
            _id = glCreateProgram();
            for (Shader * shader : shaders) {
                glAttachShader(_id, shader->_id);
            }

            glLinkProgram(_id);

            /*** Verify some things about the program ***/
            GLint linkedSuccessfully;
            GLint logLength;

            glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                GLchar *log = new GLchar[logLength];
                glGetProgramInfoLog(_id, logLength, NULL, log);
                std::cout << log << std::endl;
                delete [] log;
            }

            glGetProgramiv(_id, GL_LINK_STATUS, &linkedSuccessfully);
            if (linkedSuccessfully != GL_TRUE) {
                throw std::runtime_error("Shader program did not link");
            }
        }

        ShaderProgram::ShaderProgram(ShaderProgram && other)
        {
            this->_id = other._id;
            
            other._id = 0;
        }

        ShaderProgram::~ShaderProgram()
        {
            glDeleteProgram(_id);
        }

        void ShaderProgram::makeActive()
        {
            glUseProgram(_id);
        }

        GLuint ShaderProgram::getID()
        {
            return _id;
        }

        GLuint ShaderProgram::getUniformLocation(const char identifier[])
        {
            return glGetUniformLocation(_id, identifier);
        }

        GLuint ShaderProgram::getUniformLocation(const string identifier)
        {
            return getUniformLocation(identifier.c_str());
        }
    }
}