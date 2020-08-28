#version 450
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 normal;

uniform mat4 model;

void main() {
    gl_Position = vec4(aPos, 1.0);

    normal = aNormal;
}
