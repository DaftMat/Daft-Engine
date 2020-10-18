#version 450
#define MAX_TEX 32

layout (location = 0) out vec4 out_color;

in vec2 texCoords;

uniform sampler2D quadTexture[MAX_TEX];

void main() {
    vec3 color = texture2D(quadTexture[0], texCoords).rgb;
    out_color = vec4(color, 1.0);
}
