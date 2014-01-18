/**************************************************************************************************
 * Title:         OpenGLRenderer.h
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-15
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#pragma once

#include "Renderer.h"
#include "OpenGL.h"
#include "OpenGL_BufferObject.h"

#include <memory>

#include "PixelData.h"

#include <exception>
#include <stdexcept>

#include <map>

using std::vector;
using std::unique_ptr;

namespace evansbros { namespace graphics {
    using namespace evansbros::OpenGL;

    class OpenGLRenderer : public Renderer {
    private:
        /* Shader Program Attribute Locations */
        const GLuint VERTEX_COORDINATE_LOCATION  = 0;
        const GLuint VERTEX_COLOR_LOCATION       = 1;
        const GLuint VERTEX_POSITION_LOCATION    = 2;
        const GLuint TEXTURE_COORDINATE_LOCATION = 3;

        std::map<string, GLuint> shaderPrograms;
        std::map<string, GLuint> GPU_Textures;
        GLint currentProgram;

        struct {
            GLint x;
            GLint y;
            GLint width;
            GLint height;
        } viewport;

        GLuint vertexArrayObject;
        unique_ptr<BufferObject> vertexBufferObject = nullptr;
        unique_ptr<BufferObject> elementBufferObject = nullptr;
        unique_ptr<BufferObject> quadElementBufferObject = nullptr;

        GLuint loadShaderFromFile(const string filename, GLenum shaderType);
        GLuint loadShader(const string source, GLenum shaderType);

        void loadGPU_Textures();
        void loadGPU_Textures(const std::vector<string> & textureNames);

        void unloadGPU_Textures();
        void unloadGPU_Textures(const std::vector<string> & textureNames);

        GLuint loadTexture(PixelData imageData);

        void updateTextureQuality();

        void useShaderProgram(string programName);

        void updateProjectionMatrix();

        void drawQuads(Quad quad, string texture, std::vector<vector3> positions);

    public:
        virtual void setup();
        virtual void render(seconds interpolation);
        virtual void resizeViewport(natural width, natural height);
    };

} }
