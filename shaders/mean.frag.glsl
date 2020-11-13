#version 460
#define MAX_TEX 32

layout (location = 0) out vec4 out_color;

in vec2 texCoords;

uniform sampler2D quadTexture[MAX_TEX];

void main() {
    ivec2 uv0 = ivec2( (gl_FragCoord.xy - vec2(0.5)) * 2.0);
    ivec2 uv1 = ivec2( (gl_FragCoord.xy - vec2(0.5)) * 2.0) + ivec2( 1, 0 );
    ivec2 uv2 = ivec2( (gl_FragCoord.xy - vec2(0.5)) * 2.0) + ivec2( 1, 1 );
    ivec2 uv3 = ivec2( (gl_FragCoord.xy - vec2(0.5)) * 2.0) + ivec2( 0, 1 );

    vec4 p0 = texelFetch(quadTexture[0], uv0, 0);
    vec4 p1 = texelFetch(quadTexture[0], uv1, 0);
    vec4 p2 = texelFetch(quadTexture[0], uv2, 0);
    vec4 p3 = texelFetch(quadTexture[0], uv3, 0);

    float lumSum = p0.x + p1.x + p2.x + p3.x;
    float lumMin = min(min(p0.x, p1.x), min(p2.x, p3.x));
    float lumMax = max(max(p0.x, p1.x), max(p2.x, p3.x));
    out_color = vec4(lumSum, lumMin, lumMax, 1.0);
}
