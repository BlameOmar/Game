//
//  OpenGLRender.cpp
//  OpenGL Practice
//
//  Created by Omar Stefan Evans on 11/15/13.
//  Copyright (c) 2013 MainChat. All rights reserved.
//

#include "OpenGLRender.h"

#include <fstream>
#include "utilities.h"

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

    std::cout << glGetString( GL_VERSION ) << std::endl;

    /* Enable some attributes */
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_MULTISAMPLE);

    /* Create a Vertex Buffer Object */
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &elementBufferObject);
    glGenVertexArrays(1, &vertexArrayObject);

    /* Load the shaders */
    std::unordered_map<string, GLuint> shaders;

    shaders["defaultVertexShader"] = loadShaderFromFile("shaders/default.vsh", GL_VERTEX_SHADER);
    shaders["defaultFragmentShader"] = loadShaderFromFile("shaders/default.fsh", GL_FRAGMENT_SHADER);

    /* Link the shaders into programs */
    GLuint program;
    /** Default Shader Program **/
    program = glCreateProgram();
    glAttachShader(program, shaders["defaultVertexShader"]);
    glAttachShader(program, shaders["defaultFragmentShader"]);

    glBindFragDataLocation(program, 0, "outColor");

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

    textures["test"] = loadTextureFromFile("textures/rainbow");

    /* Mark the shaders for deletion */
    for (auto keyValuePair : shaders) {
        glDeleteShader(keyValuePair.second);
    }
}


void OpenGlRenderer::render()
{
    const GLuint POSITION_LOCATION           = 0;
    const GLuint COLOR_LOCATION              = 1;
    const GLuint TEXTURE_COORDINATE_LOCATION = 2;

    glUseProgram(shaderPrograms["default"]);

    GLfloat hexagonVerticies[] = {
        //Position (X, Y, Z)       Color (R, G, B, A)      Texture Cordinates (R, S)
        0.000f,  0.000f,  0.000f, 0.0f, 0.0f, 0.0f, 1.0f, 0.500f, 0.500f,
        0.000f,  0.500f,  0.000f, 1.0f, 0.0f, 0.0f, 1.0f, 0.500f, 1.000f,
        -0.433f,  0.250f,  0.000f, 1.0f, 1.0f, 0.0f, 1.0f, 0.133f, 0.750f,
        -0.433f, -0.250f,  0.000f, 0.0f, 1.0f, 0.0f, 1.0f, 0.133f, 0.250f,
        0.000f, -0.500f,  0.000f, 0.0f, 1.0f, 1.0f, 1.0f, 0.500f, 0.000f,
        0.433f, -0.250f,  0.000f, 0.0f, 0.0f, 1.0f, 1.0f, 0.933f, 0.250f,
        0.433f,  0.250f,  0.000f, 1.0f, 0.0f, 1.0f, 1.0f, 0.933f, 0.750f
    };

    GLint hexagonElements[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 1
    };

    GLfloat vertices[] = {
        //Position (X, Y, Z)       Color (R, G, B, A)      Texture Cordinates (R, S)
        0.000f,  0.000f,  0.000f, 1.0f, 0.0f, 0.0f, 1.0f, 0.000f, 0.000f,
        1.000f,  0.000f,  0.000f, 0.0f, 1.0f, 0.0f, 1.0f, 1.000f, 0.000f,
        1.000f,  1.000f,  0.000f, 0.0f, 0.0f, 1.0f, 1.0f, 1.000f, 1.000f,
        0.000f,  1.000f,  0.000f, 1.0f, 1.0f, 1.0f, 1.0f, 0.000f, 1.000f,
    };

    GLint elements[] = {
        0, 1, 2,
        2, 3, 0,
    };


    GLfloat modelMatrix[16] {
        1.0000,  0.0000,  0.0000,  0.0000,
        0.0000,  1.0000,  0.0000,  0.0000,
        0.0000,  0.0000,  1.0000,  0.0000,
        0.0000,  0.0000,  0.0000,  1.0000
    };

    modelMatrix[0 * 4 + 3] = gameState->playerState.x;
    modelMatrix[1 * 4 + 3] = gameState->playerState.y;

    GLfloat viewMatrix[16] {
        1.0000/2
        ,   0.0000,   0.0000,  -1.0000,
        0.0000,   1.0000/2,   0.0000,  -1.0000,
        0.0000,   0.0000,   1.0000/2,   0.0000,
        0.0000,   0.0000,   0.0000,   1.0000
    };

    GLint m_viewport[4];
    glGetIntegerv( GL_VIEWPORT, m_viewport );

    GLfloat viewportWidth = m_viewport[2];
    GLfloat viewportHeight = m_viewport[3];
    GLfloat viewportAspectRatio = viewportWidth / viewportHeight;

    GLfloat projectionMatrix[16] {
        1.0000,  0.0000,  0.0000,  0.0000,
        0.0000,  1.0000,  0.0000,  0.0000,
        0.0000,  0.0000,  1.0000,  0.0000,
        0.0000,  0.0000,  0.0000,  1.0000
    };

    projectionMatrix[0] /= viewportAspectRatio;

    glBindVertexArray( vertexArrayObject );
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glBindTexture(GL_TEXTURE_2D, textures["test"]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLint modelMatrixUniform = glGetUniformLocation(shaderPrograms["default"], "model");
    glUniformMatrix4fv(modelMatrixUniform, 1, GL_TRUE, modelMatrix);

    GLint viewMatrixUniform = glGetUniformLocation(shaderPrograms["default"], "view");
    glUniformMatrix4fv(viewMatrixUniform, 1, GL_TRUE, viewMatrix);

    GLint projectionMatrixUniform = glGetUniformLocation(shaderPrograms["default"], "projection");
    glUniformMatrix4fv(projectionMatrixUniform, 1, GL_TRUE, projectionMatrix);


    //    GLint positionAtrribute = glGetAttribLocation(shaderPrograms["default"], "position");
    //    glVertexAttribPointer(positionAtrribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
    //    glEnableVertexAttribArray(positionAtrribute);
    glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
    glEnableVertexAttribArray(POSITION_LOCATION);


    //    GLint colorAttribute = glGetAttribLocation(shaderPrograms["default"], "color");
    //    glVertexAttribPointer(colorAttribute, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid *)(3 * sizeof(float)));
    //    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(COLOR_LOCATION, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid *)(3 * sizeof(float)));
    glEnableVertexAttribArray(COLOR_LOCATION);


    //    GLint textureCoordinateAttribute = glGetAttribLocation(shaderPrograms["default"], "textureCoordinate");
    //    glVertexAttribPointer(textureCoordinateAttribute, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid *)(7 * sizeof(float)));
    //    glEnableVertexAttribArray(textureCoordinateAttribute);
    glVertexAttribPointer(TEXTURE_COORDINATE_LOCATION, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (GLvoid *)(7 * sizeof(float)));
    glEnableVertexAttribArray(TEXTURE_COORDINATE_LOCATION);

    glClearColor (0.0, 0.0, 0.0, 1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_FRAMEBUFFER_SRGB);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDisable(GL_FRAMEBUFFER_SRGB);
    
    glFlush();
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

GLuint OpenGlRenderer::loadTextureFromFile(const string filename) {
    const string suffixes[] {"_1.png", "_2.png", "_4.png", "_8.png", "_16.png", "_32.png", "_64.png", "_128.png", "_256.png", "_512.png", "_1024.png"};

    natural quality = 9;  // maximum pixel dimension = 2^(quality)

    Data data;
    vector<ImageData> imageVector(quality + 1);

    for (natural i = 0; i <= quality; ++i) {
        data = loadAsset(filename + suffixes[quality - i]);
        imageVector[i] = decodePNGData(data);
    }

    GLuint texture = loadTexture(imageVector);

    return texture;
}

GLuint OpenGlRenderer::loadTexture(const vector<ImageData> imageVector) {
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    for (size_t i = 0; i < imageVector.size(); ++i) {
        ImageData imageData = imageVector[i];
        GLint level = (GLint) i;

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
    }

    return texture;
}
