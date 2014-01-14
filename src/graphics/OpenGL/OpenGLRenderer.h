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

#include "PixelData.h"

#include <exception>
#include <stdexcept>

#include <map>

using std::vector;

namespace evansbros { namespace graphics {
    class OpenGLRenderer : public Renderer {
    private:
        std::map<string, GLuint> shaderPrograms;
        std::map<string, GLuint> GPU_Textures;

        struct {
            GLint x;
            GLint y;
            GLint width;
            GLint height;
        } viewport;

        GLuint vertexArrayObject;
        GLuint vertexBufferObject;
        GLuint elementBufferObject;

        GLuint loadShaderFromFile(const string filename, GLenum shaderType);
        GLuint loadShader(const string source, GLenum shaderType);

        void loadGPU_Textures();
        void loadGPU_Textures(const std::vector<string> & textureNames);

        void unloadGPU_Textures();
        void unloadGPU_Textures(const std::vector<string> & textureNames);

        GLuint loadTexture(PixelData imageData);

        void updateTextureQuality();

        void drawQuads(Quad quad, string texture, std::vector<vector3> positions);

        void beginDrawing();
        void endDrawing();

    public:
        virtual void setup();
        virtual void render(seconds interpolation);
        virtual void resizeViewport(natural width, natural height);
    };

} }
