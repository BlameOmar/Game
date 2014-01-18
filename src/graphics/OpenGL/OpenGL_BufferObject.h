/**************************************************************************************************
 * Title:         OpenGL_BufferObject.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "OpenGL.h"
#include "Data.h"

namespace evansbros {
    namespace OpenGL {

        struct Range {
            GLsizeiptr begining;
            GLsizeiptr end;
        };

        class BufferObject{
        public:
            BufferObject();
            BufferObject(GLsizeiptr size, GLenum usage);
            ~BufferObject();

            GLsizeiptr size() const;
            GLenum usage() const;

            void bindTo(GLenum target) const;

            void setData(Data data, GLenum usage);
            void updateData(Data data, GLsizeiptr bufferOffset = 0);
        private:
            GLsizeiptr  _size           = 0;
            GLenum      _usage          = GL_STREAM_DRAW;
            GLuint      _bufferObjectID = 0;
        };

    }
}