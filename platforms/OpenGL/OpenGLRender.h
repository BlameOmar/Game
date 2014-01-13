//
//  OpenGLRender.h
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/15/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#ifndef __OpenGL_Practice__OpenGLRender__
#define __OpenGL_Practice__OpenGLRender__

#include "Renderer.h"
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>

#include "types.h"
#include "PixelData.h"
#include "vector.h"

#include <exception>
#include <stdexcept>

#include <map>
#include <vector>

using std::vector;

namespace evansbros {

    struct Quad {
        math::vector v1;
        math::vector v2;
        math::vector v3;
        math::vector v4;

        Quad() = delete;
        Quad(math::vector v1, math::vector v2, math::vector v3 ,math::vector v4) : v1(v1), v2(v2), v3(v3), v4(v4) {}
    };

    struct Color {
        real red   = 0.0;
        real green = 0.0;
        real blue  = 0.0;
        real alpha = 0.0;

        Color() = default;
        Color(real red, real green, real blue, real alpha) : red(red), green(green), blue(blue), alpha(alpha) {}
    };

    class OpenGlRenderer : public Renderer {
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

        virtual void drawQuad(Quad quad, math::vector position, Color color, string texture);

    public:
        virtual void setup();
        virtual void render(seconds interpolation);
        virtual void resizeViewport(real width, real height);
    };

}

#endif /* defined(__OpenGL_Practice__OpenGLRender__) */
