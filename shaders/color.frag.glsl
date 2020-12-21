#version 450
out vec4 out_color;

in vec3 fragWeights;

uniform vec3 color;
uniform bool isAnimated;

void main() {
    if (isAnimated)
        out_color = vec4(fragWeights, 1.0);
    else
        out_color = vec4(color, 1.0);
}
