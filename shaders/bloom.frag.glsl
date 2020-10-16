#version 460
#define MAX_TEX 32

layout (location = 0) out vec4 out_color;

in vec2 texCoords;

uniform sampler2D quadTexture[MAX_TEX];

uniform float threshold;

void main() {
    out_color = vec4(vec3(0.0), 1.0);
    vec3 hdrColor = texture2D(quadTexture[0], texCoords).rgb;
    if (dot(hdrColor, vec3(0.2126, 0.7152, 0.0722)) > threshold)
        out_color = vec4(hdrColor, 1.0);
}
