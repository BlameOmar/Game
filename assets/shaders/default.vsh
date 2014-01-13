#version 330
#define POSITION_LOCATION            0
#define COLOR_LOCATION               1
#define TEXTURE_COORDINATE_LOCATION  2

layout(location = POSITION_LOCATION) in vec3 position;
layout(location = COLOR_LOCATION) in vec4 color;
layout(location = TEXTURE_COORDINATE_LOCATION) in vec2 textureCoordinate;

out vec4 Color;
out vec2 TextureCoordinate;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    Color = color;
    TextureCoordinate = vec2(textureCoordinate.s, -1.0 * textureCoordinate.t);
    gl_Position = projection * view * model * vec4(position, 1.0);
}