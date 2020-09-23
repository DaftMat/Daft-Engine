#version 450
layout (location = 0) out vec4 out_color;

in vec2 texCoords;

uniform sampler2D quadTexture;

void main() {
    out_color = texture(quadTexture, texCoords);
}
