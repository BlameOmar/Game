/**************************************************************************************************
 * Title:         OpenGL_BufferObject.h
 * Author:        Omar Stefan Evans
 * Created on:    2014-01-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "OpenGL_BufferObject.h"
#include <stdexcept>

namespace evansbros {
    namespace OpenGL {

        BufferObject::BufferObject() : _size(0)
        {
            glGenBuffers(1, &_bufferObjectID);
        }

        BufferObject::BufferObject(GLsizeiptr size, GLenum usage) : _size(size), _usage(usage)
        {
            glGenBuffers(1, &_bufferObjectID);
            glBindBuffer(GL_COPY_WRITE_BUFFER, _bufferObjectID);
            glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, usage);
            glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        }

        BufferObject::~BufferObject()
        {
            glDeleteBuffers(1, &_bufferObjectID);
        }

        GLsizeiptr BufferObject::size() const
        {
            return _size;
        }

        GLenum BufferObject::usage() const
        {
            return _usage;
        }

        void BufferObject::bindTo(GLenum target) const
        {
            glBindBuffer(target, _bufferObjectID);
        }

        void BufferObject::setData(Data data, GLenum usage)
        {
            _size = data.getSize();
            _usage = usage;
            
            glBindBuffer(GL_COPY_WRITE_BUFFER, _bufferObjectID);
            glBufferData(GL_COPY_WRITE_BUFFER, data.getSize(), data.getBytes(), usage);
            glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        }

        void BufferObject::updateData(Data data, GLsizeiptr bufferOffset)
        {
            if (bufferOffset + data.getSize() > _size) {
                throw std::out_of_range("The supplied data would exceed the bounds of the buffer object");
            }
            glBindBuffer(GL_COPY_WRITE_BUFFER, _bufferObjectID);
            glBufferSubData(GL_COPY_WRITE_BUFFER, bufferOffset, data.getSize(), data.getBytes());
            glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
        }
        
    }
}