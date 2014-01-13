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

#include "types.h"
#include <iostream>
#include <exception>
#include <stdexcept>

#include <unordered_map>
#include <vector>

#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>

#include "ImageData.h"

using std::vector;

class OpenGlRenderer : public Renderer {
private:
    std::unordered_map<string, GLuint> shaderPrograms;
    std::unordered_map<string, GLuint> textures;

    GLuint vertexArrayObject;
    GLuint vertexBufferObject;
    GLuint elementBufferObject;

    GLuint loadShaderFromFile(const string filename, GLenum shaderType);
    GLuint loadShader(const string source, GLenum shaderType);

    GLuint loadTextureFromFile(const string filename);
    GLuint loadTexture(const vector<ImageData> imageVector);
public:
    virtual void setup();
    virtual void render();
};

#endif /* defined(__OpenGL_Practice__OpenGLRender__) */
