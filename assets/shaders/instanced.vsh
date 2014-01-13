#version 330
#define VERTEX_COORDINATE_LOCATION   0
#define VERTEX_COLOR_LOCATION        1
#define VERTEX_POSITION_LOCATION     2
#define TEXTURE_COORDINATE_LOCATION  3

layout(location = VERTEX_COORDINATE_LOCATION)  in vec3 vertexCoordinate;
layout(location = VERTEX_COLOR_LOCATION)       in vec4 vertexColor;
layout(location = VERTEX_POSITION_LOCATION)    in vec3 vertexPosition;
layout(location = TEXTURE_COORDINATE_LOCATION) in vec2 textureCoordinate;


out vec4 Color;
out vec2 TextureCoordinate;

uniform mat4 view;
uniform mat4 projection;

void main() {
    Color = vertexColor;
    TextureCoordinate = vec2(textureCoordinate.s, -1.0 * textureCoordinate.t);

    mat4 model = mat4(1.0);
    model[3] = vec4(vertexPosition, model[3][3]);

    gl_Position = projection * view * model * vec4(vertexCoordinate, 1.0);
}