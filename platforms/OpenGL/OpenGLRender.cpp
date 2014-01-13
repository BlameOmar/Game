/**************************************************************************************************
 * Title:         <#Title#>
 * Author:        Omar Stefan Evans
 * Created on:    <#Date#>
 * Description:   <#Description#>
 * Purpose:       <#Purpose#>
 * Modifications: <#Modifications#>
 **************************************************************************************************/

#include "OpenGLRender.h"

#include "utilities.h"
#include "matrix.h"

#include <iostream>

namespace evansbros {

    unsigned int printOpenGLError() {
        GLenum error = GL_NO_ERROR;
        unsigned int numberOfErrors = 0;
        do {
            error = glGetError();
            if (error == GL_NO_ERROR) {
                continue;
            } else switch (error) {
                case GL_INVALID_ENUM:
                    std::cout<< "An unacceptable value is specified for an enumerated argument.\n";
                    break;
                case GL_INVALID_VALUE:
                    std::cout << "A numeric argument is out of range.\n";
                    break;
                case GL_INVALID_OPERATION:
                    std::cout << "The specified operation is not allowed in the current state.\n";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    std::cout << "The framebuffer object is not complete.\n";
                    break;
                case GL_OUT_OF_MEMORY:
                    std::cout << "There is not enough memory left to execute the command.\n";
                    break;
                default:
                    std::cout << "Unknown OpenGl error.\n";
            }
            ++numberOfErrors;
        } while (error != GL_NO_ERROR);

        return numberOfErrors;
    }

    void OpenGlRenderer::setup() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        std::cout << glGetString( GL_VERSION ) << std::endl;

        /* Enable some attributes */
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_MULTISAMPLE);

        /* Set the viewport attributes */
        glGetIntegerv( GL_VIEWPORT, (GLint *)&viewport );

        /* Set the texture quality */
        updateTextureQuality();

        /* Create a Vertex Buffer Object */
        glGenBuffers(1, &vertexBufferObject);
        glGenBuffers(1, &elementBufferObject);
        glGenVertexArrays(1, &vertexArrayObject);

        /* Load the shaders */
        std::map<string, GLuint> shaders;

        shaders["defaultVertexShader"] = loadShaderFromFile("shaders/default.vsh", GL_VERTEX_SHADER);
        shaders["defaultFragmentShader"] = loadShaderFromFile("shaders/default.fsh", GL_FRAGMENT_SHADER);

        /* Link the shaders into programs */
        GLuint program;
        /** Default Shader Program **/
        program = glCreateProgram();

        glAttachShader(program, shaders["defaultVertexShader"]);
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
    }


    void OpenGlRenderer::render(seconds interpolation)
    {
        glUseProgram(shaderPrograms["default"]);

        math::matrix viewMatrix = math::matrix::identity(4);
        math::matrix projectionMatrix = math::matrix::identity(4);

        math::vector cameraPosition = gameState->cameraState.position + gameState->cameraState.velocity * interpolation.count();

        viewMatrix(0,3) = -cameraPosition.getX();
        viewMatrix(1,3) = -cameraPosition.getY();
        viewMatrix(2,3) = -cameraPosition.getZ();

        GLfloat viewportAspectRatio = (GLfloat) viewport.width / viewport.height;

        projectionMatrix(0, 0) /= viewportAspectRatio;

        projectionMatrix(0, 0) *= viewportAspectRatio / 10;
        projectionMatrix(1, 1) *= viewportAspectRatio / 10;
        projectionMatrix(2, 2) *= viewportAspectRatio / 10;

        GLint viewMatrixUniform = glGetUniformLocation(shaderPrograms["default"], "view");
        glUniformMatrix4fv(viewMatrixUniform, 1, GL_TRUE, viewMatrix.getData());

        GLint projectionMatrixUniform = glGetUniformLocation(shaderPrograms["default"], "projection");
        glUniformMatrix4fv(projectionMatrixUniform, 1, GL_TRUE, projectionMatrix.getData());

        glClearColor (0.0, 0.0, 0.0, 1.0);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_FRAMEBUFFER_SRGB);

        std::map<natural, string> tilemap_texture_definitions;
        tilemap_texture_definitions[0] = "grass";
        tilemap_texture_definitions[1] = "dirt";
        tilemap_texture_definitions[2] = "cobblestone";
        tilemap_texture_definitions[3] = "water";
        tilemap_texture_definitions[4] = "sand";

        const natural tilemap_width = 20;
        const natural tilemap_height = 14;
        natural tilemap[tilemap_height][tilemap_width] {
            {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            {1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
            {4, 4, 4, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {3, 3, 3, 4, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {3, 3, 3, 4, 1, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {3, 3, 3, 3, 4, 1, 0, 0, 2, 2, 0, 0, 0, 1, 4, 1, 4, 1, 0, 0},
            {3, 3, 3, 3, 4, 1, 0, 0, 2, 2, 0, 0, 0, 4, 1, 4, 1, 4, 0, 0},
            {3, 3, 3, 3, 4, 1, 0, 0, 2, 2, 0, 0, 0, 1, 4, 1, 4, 1, 0, 0},
            {3, 3, 3, 4, 1, 0, 0, 0, 2, 2, 0, 0, 0, 4, 1, 4, 1, 4, 0, 0},
            {3, 3, 4, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 4, 1, 4, 1, 0, 0},
            {4, 4, 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };


        for (natural x = 0; x < tilemap_width; ++x) {
            for (natural y = 0; y < tilemap_height; ++y) {
                drawQuad(Quad(math::vector(0.0, 0.0, 0.0), math::vector(1.0, 0.0, 0.0), math::vector(1.0, 1.0, 0.0), math::vector(0.0, 1.0, 0.0)),
                         math::vector(x - tilemap_width / 2.0, y - tilemap_height / 2.0, -1.0), Color(), tilemap_texture_definitions[tilemap[tilemap_height - y - 1][x]]);
            }
        }

        drawQuad(Quad(math::vector(0.0, 0.0, 0.0), math::vector(1.0, 0.0, 0.0), math::vector(1.0, 1.0, 0.0), math::vector(0.0, 1.0, 0.0)),
                 gameState->p1State.position + gameState->p1State.velocity * interpolation.count() - math::vector(0.5, 0.5, 0.0), Color(), "test");
        drawQuad(Quad(math::vector(0.0, 0.0, 0.0), math::vector(1.0, 0.0, 0.0), math::vector(1.0, 1.0, 0.0), math::vector(0.0, 1.0, 0.0)),
                 gameState->p2State.position + gameState->p2State.velocity * interpolation.count() - math::vector(0.5, 0.5, 0.0), Color(), "test");

        glDisable(GL_FRAMEBUFFER_SRGB);

        glFlush();
    }

    void OpenGlRenderer::resizeViewport(real width, real height) {
        viewport.width = width;
        viewport.height = height;

        updateTextureQuality();

        glViewport(0, 0, viewport.width, viewport.height);
    }

    void OpenGlRenderer::updateTextureQuality()
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

    void OpenGlRenderer::drawQuad(Quad quad, math::vector position, Color color, string texture = "") {
        const GLuint POSITION_LOCATION           = 0;
        const GLuint COLOR_LOCATION              = 1;
        const GLuint TEXTURE_COORDINATE_LOCATION = 2;

        GLfloat vertices[] {
            quad.v1.getX(), quad.v1.getY(), quad.v1.getZ(), color.red, color.green, color.blue, color.alpha, 0.0, 0.0,
            quad.v2.getX(), quad.v2.getY(), quad.v2.getZ(), color.red, color.green, color.blue, color.alpha, 1.0, 0.0,
            quad.v3.getX(), quad.v3.getY(), quad.v3.getZ(), color.red, color.green, color.blue, color.alpha, 1.0, 1.0,
            quad.v4.getX(), quad.v4.getY(), quad.v4.getZ(), color.red, color.green, color.blue, color.alpha, 0.0, 1.0
        };

        math::matrix modelMatrix = math::matrix::identity(4);

        modelMatrix(0, 3) = position.getX();
        modelMatrix(1, 3) = position.getY();
        modelMatrix(2, 3) = position.getZ();

        glBindVertexArray( vertexArrayObject );
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        GLint elements[] = {
            0, 1, 2,
            2, 3, 0,
        };

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

        if (texture != "") {
            glBindTexture(GL_TEXTURE_2D, (GPU_Textures)[texture]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        GLint modelMatrixUniform = glGetUniformLocation(shaderPrograms["default"], "model");
        glUniformMatrix4fv(modelMatrixUniform, 1, GL_TRUE, modelMatrix.getData());

        glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
        glEnableVertexAttribArray(POSITION_LOCATION);

        glVertexAttribPointer(COLOR_LOCATION, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid *)(3 * sizeof(float)));
        glEnableVertexAttribArray(COLOR_LOCATION);

        glVertexAttribPointer(TEXTURE_COORDINATE_LOCATION, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid *)(7 * sizeof(float)));
        glEnableVertexAttribArray(TEXTURE_COORDINATE_LOCATION);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    }

    GLuint OpenGlRenderer::loadShaderFromFile(const string filename, GLenum shaderType) {
        Data shaderData = loadAsset(filename);
        string shaderSource = string((char *)shaderData.getBytes(), shaderData.getSize());

        GLuint shader = loadShader(shaderSource, shaderType);

        return shader;
    }

    GLuint OpenGlRenderer::loadShader(const string source, GLenum shaderType) {
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

    void OpenGlRenderer::loadGPU_Textures()
    {
        for (auto texture : (*textures).at(textureQuality)) {
            GPU_Textures[texture.first] = loadTexture(texture.second);
        }
    }

    void OpenGlRenderer::loadGPU_Textures(const std::vector<string> & textureNames)
    {
        for (string textureName : textureNames) {
            GPU_Textures[textureName] = loadTexture(textures->at(textureQuality).at(textureName));
        }
    }

    void OpenGlRenderer::unloadGPU_Textures()
    {
        std::vector<GLuint> textureHandles;

        for (auto texture : GPU_Textures) {
            textureHandles.push_back(texture.second);
        }

        glDeleteTextures((GLsizei)textureHandles.size(), textureHandles.data());
    }

    void OpenGlRenderer::unloadGPU_Textures(const std::vector<string> & textureNames)
    {
        std::vector<GLuint> textureHandles;

        for (string textureName : textureNames) {
            textureHandles.push_back(GPU_Textures[textureName]);
        }

        glDeleteTextures((GLsizei)textureHandles.size(), textureHandles.data());
    }

    GLuint OpenGlRenderer::loadTexture(PixelData imageData)
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
}

