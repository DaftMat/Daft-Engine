#version 460
#define MAX_TEX 32

layout (location = 0) out vec4 out_color;

in vec2 texCoords;

uniform sampler2D quadTexture[MAX_TEX];

void main() {
    vec3 color1 = texture2D(quadTexture[0], texCoords).rgb;
    vec3 color2 = texture2D(quadTexture[1], texCoords).rgb;
    vec3 resColor = color1 + color2;
    out_color = vec4(resColor, 1.0);
}
