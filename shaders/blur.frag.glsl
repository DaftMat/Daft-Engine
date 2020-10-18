#version 460
#define MAX_TEX 32

layout (location = 0) out vec4 out_color;

in vec2 texCoords;

uniform sampler2D quadTexture[MAX_TEX];

float kernel[5][5] = {
    {1.0,  4.0,  7.0,  4.0, 1.0},
    {4.0, 16.0, 26.0, 16.0, 4.0},
    {7.0, 26.0, 41.0, 26.0, 7.0},
    {4.0, 16.0, 26.0, 16.0, 4.0},
    {1.0,  4.0,  7.0,  4.0, 1.0}
};

void main() {
    vec3 color = vec3(0.0);
    vec2 texSize = textureSize(quadTexture[0], 0);
    vec2 texelSize = 1.f / texSize;

    for (int x = -2 ; x <= 2 ; ++x) {
        for (int y = -2 ; y <= 2 ; ++y) {
            color += texture2D(quadTexture[0], texCoords + vec2(x,y) * texelSize).rgb * kernel[x+2][y+2];
        }
    }
    color = color / 273.0;

    out_color = vec4(color, 1.0);
}
