/**************************************************************************************************
 * Title:         OpenGL_ShaderProgram.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-19
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "OpenGL_ShaderObject.h"
#include <initializer_list>

namespace evansbros {
    namespace OpenGL {

        class ShaderProgram {
        public:
            ShaderProgram() = default;
            ShaderProgram(std::initializer_list<ShaderObject *> shaderObjects);
            ShaderProgram(const ShaderProgram & other) = delete;
            ShaderProgram(ShaderProgram && other);
            ~ShaderProgram();

            void makeActive();
            GLuint getID();
            GLuint getUniformLocation(const char identifier[]);
            GLuint getUniformLocation(const string identifier);
        private:
            GLuint _id = 0;
        };

    }
}