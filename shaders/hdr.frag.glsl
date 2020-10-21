#version 460
#define MAX_TEX 32

layout (location = 0) out vec4 out_color;

in vec2 texCoords;

mat3 acesInput = mat3(
0.59719, 0.07600, 0.02840,
0.35458, 0.90834, 0.13383,
0.04823, 0.01566, 0.83777
);

mat3 acesOutput = mat3(
 1.60475, -0.10208, -0.00327,
-0.53108,  1.10813, -0.07276,
-0.07367, -0.00605,  1.07602
);

uniform sampler2D quadTexture[MAX_TEX];
//uniform float exposure;

vec3 aces_approx(vec3 v);
vec3 RRTandODTFit(vec3 v);

void main() {
    vec3 color = texture2D(quadTexture[0], texCoords).rgb;
    color = aces_approx(color);
    //color = pow(color, vec3(1.0 / 2.2));
    out_color = vec4(color, 1.0);
}

vec3 aces_approx(vec3 v)
{
    //v = acesInput * v;
    //v = RRTandODTFit(v);
    //v = acesOutput * v;
    v *= 0.6;
    float a = 2.51f;
    float b = 0.03f;
    float c = 2.43f;
    float d = 0.59f;
    float e = 0.14f;
    v = (v*(a*v+b))/(v*(c*v+d)+e);
    return clamp(v, 0.0, 1.0);
}

vec3 RRTandODTFit(vec3 v)
{
    vec3 a = v * (v + 0.0245786) - 0.000090537;
    vec3 b = v * (0.983729 * v + 0.4329510) + 0.238081;
    return a / b;
}