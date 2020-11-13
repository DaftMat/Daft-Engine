#version 460
#define MAX_TEX 32

layout (location = 0) out vec4 out_color;

in vec2 texCoords;

uniform sampler2D quadTexture[MAX_TEX];

void main() {
    vec3 color = texture2D(quadTexture[0], texCoords).rgb;
    float lum = dot(color, vec3(0.2126, 0.7152, 0.0722));
    out_color = vec4(vec3(lum), 1.0);
}
