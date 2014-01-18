/**************************************************************************************************
 * Title:         OpenGLRenderer.cpp
 * Author:        Omar Stefan Evans
 * Created on:    2013-11-15
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "OpenGLRenderer.h"

#include "utilities.h"
#include "OpenGL_utilities.h"
#include "matrix.h"

#include <iostream>

namespace evansbros { namespace graphics {

    void OpenGLRenderer::setup() {
        std::cout << glGetString( GL_VERSION ) << std::endl;

        /* Enable some attributes */
        glEnable (GL_DEPTH_TEST);
        glDepthRange(1.0, 0.0);
        glDepthFunc(GL_LEQUAL);

        glEnable (GL_MULTISAMPLE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glEnable(GL_FRAMEBUFFER_SRGB);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        /* Set the viewport attributes */
        glGetIntegerv( GL_VIEWPORT, (GLint *)&viewport );

        /* Set the texture quality */
        updateTextureQuality();

        /* Create a VertexArrayObject */
        glGenVertexArrays(1, &vertexArrayObject);

        /* Create a vertex BufferObject and element BufferObject */
        vertexBufferObject = unique_ptr<BufferObject>{ new BufferObject() };
        elementBufferObject = unique_ptr<BufferObject>{ new BufferObject() };

        /* Create the Quad element BufferObject */
        GLint quadElements[2][3] {{0, 1, 2}, {2, 3, 0}};
        quadElementBufferObject = unique_ptr<BufferObject>{ new BufferObject() };
        quadElementBufferObject->setData({sizeof(quadElements), (byte *)quadElements}, GL_STATIC_DRAW);

        /* Load the shaders */
        std::map<string, GLuint> shaders;

        shaders["instancedVertexShader"] = loadShaderFromFile("shaders/instanced.vsh", GL_VERTEX_SHADER);
        shaders["defaultFragmentShader"] = loadShaderFromFile("shaders/default.fsh", GL_FRAGMENT_SHADER);

        /* Link the shaders into programs */
        GLuint program;

        /** Default Shader Program **/
        program = glCreateProgram();

        glAttachShader(program, shaders["instancedVertexShader"]);
        glAttachShader(program, shaders["defaultFragmentShader"]);
        glLinkProgram(program);

        /*** Verify some things about the program ***/
        GLint linkedSuccessfully;
        GLint logLength;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = new GLchar[logLength];
            glGetProgramInfoLog(program, logLength, NULL, log);
            std::cout << log << std::endl;
            delete [] log;
        }

        glGetProgramiv(program, GL_LINK_STATUS, &linkedSuccessfully);
        if (linkedSuccessfully != GL_TRUE) {
            throw std::runtime_error("Shader program did not link");
        }

        shaderPrograms["default"] = program;

        loadGPU_Textures();

        /* Mark the shaders for deletion */
        for (auto keyValuePair : shaders) {
            glDeleteShader(keyValuePair.second);
        }

        /* Set the current program */
        useShaderProgram("default");
    }

    void OpenGLRenderer::render(seconds interpolation)
    {
        math::matrix viewMatrix = math::matrix::identity(4);

        vector3 cameraPosition = gameState->cameraState.position + gameState->cameraState.velocity * interpolation.count();

        viewMatrix(0,3) = -cameraPosition.x;
        viewMatrix(1,3) = -cameraPosition.y;
        viewMatrix(2,3) = -cameraPosition.z;

        GLint viewMatrixUniform = glGetUniformLocation(currentProgram, "view");
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_TRUE, viewMatrix.getData());

        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawTileMap();

        Quad uncoloredQuad({{0.0, 0.0}, Color()}, {{1.0, 0.0}, Color()}, {{1.0, 1.0}, Color()}, {{0.0, 1.0}, Color()});

        drawQuads(uncoloredQuad, "test",
                  {
                      gameState->p1State.position + gameState->p1State.velocity * interpolation.count() - vector3(0.5, 0.5, 0.0),
                      gameState->p2State.position + gameState->p2State.velocity * interpolation.count() - vector3(0.5, 0.5, 0.0)
                  });
    }

    void OpenGLRenderer::useShaderProgram(string programName)
    {
        GLuint programID = shaderPrograms[programName];
        glUseProgram(programID);
        currentProgram = programID;

        /* Update Dependencies */
        updateProjectionMatrix();
    }

    void OpenGLRenderer::resizeViewport(natural width, natural height)
    {
        glViewport(0, 0, width, height);

        viewport.width = width;
        viewport.height = height;

        /* Update Dependencies */
        updateTextureQuality();
        updateProjectionMatrix();
    }

    void OpenGLRenderer::updateProjectionMatrix()
    {
        math::matrix projectionMatrix = math::matrix::identity(4);
        GLfloat viewportAspectRatio = (GLfloat) viewport.width / viewport.height;

        projectionMatrix(0, 0) /= viewportAspectRatio;

        projectionMatrix(0, 0) *= viewportAspectRatio / 10;
        projectionMatrix(1, 1) *= viewportAspectRatio / 10;
        projectionMatrix(2, 2) *= viewportAspectRatio / 10;

        GLint projectionMatrixUniform = glGetUniformLocation(currentProgram, "projection");
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_TRUE, projectionMatrix.getData());
    }

    void OpenGLRenderer::updateTextureQuality()
    {
        if (viewport.height >= 2160) {
            setTextureQuality(TextureQuality::ULTRA_HD);
        } else if (viewport.height >= 1440) {
            setTextureQuality(TextureQuality::QUAD_HD);
        } else if (viewport.height >= 1080) {
            setTextureQuality(TextureQuality::FULL_HD);
        } else if (viewport.height >= 720) {
            setTextureQuality(TextureQuality::HD);
        } else if (viewport.height >= 540) {
            setTextureQuality(TextureQuality::qHD);
        } else if (viewport.height >= 360) {
            setTextureQuality(TextureQuality::nHD);
        } else {
            setTextureQuality(TextureQuality::nHD);
        }
    }

    void OpenGLRenderer::drawQuads(Quad quad, string texture, std::vector<vector3> positions)
    {
        GLfloat vertexData[4][9] {
            {
                quad.v1.position.x,
                quad.v1.position.y,
                quad.v1.position.z,
                quad.v1.color.red(),
                quad.v1.color.green(),
                quad.v1.color.blue(),
                quad.v1.color.alpha(),
                0.0, 0.0
            },
            {
                quad.v2.position.x,
                quad.v2.position.y,
                quad.v2.position.z,
                quad.v2.color.red(),
                quad.v2.color.green(),
                quad.v2.color.blue(),
                quad.v2.color.alpha(),
                1.0, 0.0
            },
            {
                quad.v3.position.x,
                quad.v3.position.y,
                quad.v3.position.z,
                quad.v3.color.red(),
                quad.v3.color.green(),
                quad.v3.color.blue(),
                quad.v3.color.alpha(),
                1.0, 1.0,
            },
            {
                quad.v4.position.x,
                quad.v4.position.y,
                quad.v4.position.z,
                quad.v4.color.red(),
                quad.v4.color.green(),
                quad.v4.color.blue(),
                quad.v4.color.alpha(),
                0.0, 1.0
            }
        };

        glBindVertexArray(vertexArrayObject);

        if (vertexBufferObject->size() < sizeof(vertexData)) {
            vertexBufferObject->setData({sizeof(vertexData), (byte *)vertexData}, GL_STREAM_DRAW);
        } else {
            vertexBufferObject->updateData({sizeof(vertexData), (byte *)vertexData});
        }
        vertexBufferObject->bindTo(GL_ARRAY_BUFFER);

        glEnableVertexAttribArray(VERTEX_COORDINATE_LOCATION);
        glEnableVertexAttribArray(VERTEX_COLOR_LOCATION);
        glEnableVertexAttribArray(TEXTURE_COORDINATE_LOCATION);

        glVertexAttribPointer(VERTEX_COORDINATE_LOCATION, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
        glVertexAttribPointer(VERTEX_COLOR_LOCATION, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid *)(3 * sizeof(float)));
        glVertexAttribPointer(TEXTURE_COORDINATE_LOCATION, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid *)(7 * sizeof(float)));

        quadElementBufferObject->bindTo(GL_ELEMENT_ARRAY_BUFFER);

        if (texture != "") {
            glBindTexture(GL_TEXTURE_2D, (GPU_Textures)[texture]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        BufferObject positionBufferObject;
        positionBufferObject.setData({sizeof(vector3) * positions.size(), (byte *)positions.data()}, GL_DYNAMIC_DRAW);
        positionBufferObject.bindTo(GL_ARRAY_BUFFER);

        glEnableVertexAttribArray(VERTEX_POSITION_LOCATION);
        glVertexAttribPointer(VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glVertexAttribDivisor(VERTEX_POSITION_LOCATION, 1);

        glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (GLsizei) positions.size());
    }

    GLuint OpenGLRenderer::loadShaderFromFile(const string filename, GLenum shaderType) {
        Data shaderData = loadAsset(filename);
        string shaderSource = string((char *)shaderData.getBytes(), shaderData.getSize());

        GLuint shader = loadShader(shaderSource, shaderType);

        return shader;
    }

    GLuint OpenGLRenderer::loadShader(const string source, GLenum shaderType) {
        const char *source_c_str = source.c_str();

        GLuint shader = 0;

        shader = glCreateShader(shaderType);
        glShaderSource(shader, 1, &source_c_str, NULL);
        glCompileShader(shader);

        GLint compiledSuccesfully = 0;
        GLint logLength = 0;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0) {
            GLchar *log = new GLchar[logLength];
            glGetShaderInfoLog(shader, logLength, NULL, log);
            std::cerr << log << std::endl;
            delete [] log;
        }

        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiledSuccesfully);
        if (compiledSuccesfully != GL_TRUE) {
            throw std::runtime_error("Shader did not compile");
        }

        return shader;
    }

    void OpenGLRenderer::loadGPU_Textures()
    {
        for (auto texture : (*textures).at(textureQuality)) {
            GPU_Textures[texture.first] = loadTexture(texture.second);
        }
    }

    void OpenGLRenderer::loadGPU_Textures(const std::vector<string> & textureNames)
    {
        for (string textureName : textureNames) {
            GPU_Textures[textureName] = loadTexture(textures->at(textureQuality).at(textureName));
        }
    }

    void OpenGLRenderer::unloadGPU_Textures()
    {
        std::vector<GLuint> textureHandles;

        for (auto texture : GPU_Textures) {
            textureHandles.push_back(texture.second);
        }

        glDeleteTextures((GLsizei)textureHandles.size(), textureHandles.data());
    }

    void OpenGLRenderer::unloadGPU_Textures(const std::vector<string> & textureNames)
    {
        std::vector<GLuint> textureHandles;

        for (string textureName : textureNames) {
            textureHandles.push_back(GPU_Textures[textureName]);
        }

        glDeleteTextures((GLsizei)textureHandles.size(), textureHandles.data());
    }

    GLuint OpenGLRenderer::loadTexture(PixelData imageData)
    {
        GLuint texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        GLint level = 0;

        GLenum componentType;
        PixelFormat pixelFormat = imageData.getPixelFormat();

        switch (pixelFormat.channels.get()[0].type) {
            case PixelChannelType::INTEGER:
                switch (pixelFormat.channels.get()[0].numberOfBits) {
                    case 8:
                        componentType = GL_BYTE;
                        break;
                    case 16:
                        componentType = GL_SHORT;
                        break;
                    case 32:
                        componentType = GL_INT;
                        break;
                    default:
                        throw std::runtime_error("Unsupported Image Format");
                        break;
                }
                break;
            case PixelChannelType::UNSIGNED_INTEGER:
                switch (pixelFormat.channels.get()[0].numberOfBits) {
                    case 8:
                        componentType = GL_UNSIGNED_BYTE;
                        break;
                    case 16:
                        componentType = GL_UNSIGNED_SHORT;
                        break;
                    case 32:
                        componentType = GL_UNSIGNED_INT;
                        break;
                    default:
                        throw std::runtime_error("Unsupported Image Format");
                        break;
                }
                break;
            case PixelChannelType::FLOAT:
                switch (pixelFormat.channels.get()[0].numberOfBits) {
                    case 16:
                        componentType = GL_HALF_FLOAT;
                        break;
                    case 32:
                        componentType = GL_FLOAT;
                        break;
                    case 64:
                        componentType = GL_DOUBLE;
                        break;
                    default:
                        throw std::runtime_error("Unsupported Image Format");
                        break;
                }
                break;
            default:
                throw std::runtime_error("Unsupported Image Format");
                break;
        }

        glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, imageData.getWidth(), imageData.getHeight(), 0, GL_RGBA, componentType, imageData.getBytes());
        glGenerateMipmap(GL_TEXTURE_2D);

        return texture;
    }
} }
