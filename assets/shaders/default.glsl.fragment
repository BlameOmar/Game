#version 330

in vec4 Color;
in vec2 TextureCoordinate;

layout(location = 0) out vec4 outColor;

uniform sampler2D tex;

void blend(in vec4 source, in vec4 destination, out vec4 blended) {
    blended.a = source.a + destination.a * (1.0 - source.a);
    blended.rgb = source.rgb + destination.rgb * (1.0 - source.a);
}

void main() {
    float outAlpha;
    vec3 outRGB;
    
    vec4 sampledColor = texture(tex, TextureCoordinate);
    
    blend(sampledColor, Color, outColor);
}
