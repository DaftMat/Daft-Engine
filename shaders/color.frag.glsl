#version 450
out vec4 out_color;

in vec3 normal;

void main() {
    out_color = vec4(normal, 1.0);
}
