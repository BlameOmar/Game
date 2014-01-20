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
#include "OpenGL_VertexArrayObject.h"
#include "OpenGL_BufferObject.h"
#include "OpenGL_Shader.h"
#include "OpenGL_ShaderProgram.h"
#include <memory>

#include "PixelData.h"

#include <map>

using std::vector;
using std::shared_ptr;

namespace evansbros { namespace graphics {
    using namespace evansbros::OpenGL;

    class OpenGLRenderer : public Renderer {
    private:
        /* Shader Program Attribute Locations */
        const GLuint VERTEX_COORDINATE_LOCATION  = 0;
        const GLuint VERTEX_COLOR_LOCATION       = 1;
        const GLuint VERTEX_POSITION_LOCATION    = 2;
        const GLuint TEXTURE_COORDINATE_LOCATION = 3;

        std::map<string, GLuint> GPU_Textures;

        struct {
            GLint x;
            GLint y;
            GLint width;
            GLint height;
        } viewport;

        shared_ptr<ShaderProgram> currentProgram = nullptr;
        shared_ptr<ShaderProgram> defaultProgram = nullptr;

        VertexArrayObject vertexArrayObject;

        BufferObject vertexBufferObject;
        BufferObject elementBufferObject;
        BufferObject quadElementBufferObject;

        GLuint loadTexture(PixelData imageData);

        void updateTextureQuality();

        void useShaderProgram(shared_ptr<ShaderProgram> program);

        void updateViewMatrix(vector3 cameraPosition);
        void updateProjectionMatrix();

        void clearDrawing();
        void drawQuads(Quad quad, string texture, std::vector<vector3> positions);

    protected:
        virtual void loadGPU_Textures();
        virtual void loadGPU_Textures(const std::vector<string> & textureNames);
        virtual void unloadGPU_Textures();
        virtual void unloadGPU_Textures(const std::vector<string> & textureNames);
    public:
        OpenGLRenderer();

        virtual void render(seconds interpolation);
        virtual void resizeViewport(natural width, natural height);
    };

} }
