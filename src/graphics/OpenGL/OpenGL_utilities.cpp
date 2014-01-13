/**************************************************************************************************
 * Title:         OpenGL_utilities.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-12-17
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "OpenGL_utilities.h"

#include <cstdio>

namespace evansbros { namespace OpenGL {

    unsigned int printError() {
        GLenum error = GL_NO_ERROR;
        unsigned int numberOfErrors = 0;
        do {
            error = glGetError();
            if (error == GL_NO_ERROR) {
                continue;
            } else switch (error) {
                case GL_INVALID_ENUM:
                    fprintf(stderr, "An unacceptable value is specified for an enumerated argument.\n");
                    break;
                case GL_INVALID_VALUE:
                    fprintf(stderr, "A numeric argument is out of range.\n");
                    break;
                case GL_INVALID_OPERATION:
                    fprintf(stderr, "The specified operation is not allowed in the current state.\n");
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    fprintf(stderr, "The framebuffer object is not complete.\n");
                    break;
                case GL_OUT_OF_MEMORY:
                    fprintf(stderr, "There is not enough memory left to execute the command.\n");
                    break;
                default:
                    fprintf(stderr, "Unknown OpenGl error.\n");
            }
            ++numberOfErrors;
        } while (error != GL_NO_ERROR);

        return numberOfErrors;
    }

} }
