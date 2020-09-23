#version 450
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragPos = vec3(model * vec4(aPos, 1.0));
    fragNormal = normalize(mat3(transpose(inverse(model))) * aNormal);
    fragTex = aTexCoords;

    gl_Position = projection * view * vec4(fragPos, 1.0);
}
