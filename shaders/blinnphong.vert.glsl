#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTex;

out mat3 tbn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    fragPos = vec3(model * vec4(aPos, 1.0));
    fragNormal = normalize(mat3(transpose(inverse(model))) * aNormal);
    fragTex = aTexCoords;

    float sign = sign(fragNormal.z);
    float a = -1.0 / (sign + fragNormal.z);
    float b = fragNormal.x * fragNormal.y * a;
    vec3 tangent = normalize(vec3(1.0 + sign + fragNormal.x * fragNormal.x * a, sign * b, -sign * fragNormal.x));
    tangent = normalize(tangent - dot(tangent, fragNormal) * fragNormal);
    vec3 bitangent = cross(fragNormal, tangent);
    tbn = transpose(mat3(tangent, bitangent, fragNormal));

    gl_Position = projection * view * vec4(fragPos, 1.0);
}
