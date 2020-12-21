#version 460 core
#define MAX_DATA 16

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec4 aSkinWeights;
layout (location = 5) in vec4 aSkinIndices;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTex;
out vec3 fragWeights;

out mat3 tbn;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 skinMatrices[MAX_DATA];
uniform bool isAnimated;

void main() {
    fragWeights = aSkinWeights.xyz;

    fragPos = vec3(model * vec4(aPos, 1.0));
    if (isAnimated)
        fragPos = vec3((aSkinWeights.x * skinMatrices[int(aSkinIndices.x)]) * vec4(fragPos, 1.0))
                + vec3((aSkinWeights.y * skinMatrices[int(aSkinIndices.y)]) * vec4(fragPos, 1.0));

    mat4 normalMatrix = transpose(inverse(model));
    fragNormal = normalize(normalMatrix * vec4(aNormal, 0.0)).xyz;
    fragTex = aTexCoords;

    vec3 tangent = normalize(normalMatrix * vec4(aTangent, 0.0)).xyz;
    tangent = normalize(tangent - dot(tangent, fragNormal) * fragNormal);
    vec3 bitangent = normalize(cross(fragNormal, tangent));
    tbn = transpose(mat3(tangent, bitangent, fragNormal));

    gl_Position = projection * view * vec4(fragPos, 1.0);
}
