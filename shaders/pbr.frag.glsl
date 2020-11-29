#version 460 core
layout (location = 0) out vec4 fragColor;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTex;

in mat3 tbn;

#define MAX_SIZE 32

struct Shadow {
    sampler2D shadowMap;
    mat4 lightSpaceMatrix;
};

struct PointLight {
    Shadow shadowData;

    vec3 position;
    float intensity;
    vec3 color;
};

struct DirLight {
    Shadow shadowData;

    vec3 direction;
    vec3 color;
};

struct SpotLight {
    Shadow shadowData;

    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;
    float intensity;
    vec3 color;
};

struct QuadLight {
    vec3 points[4];
    float intensity;
    float color;
};

struct Material {
    int nrAlbedoTex;
    int nrSpecularTex;
    int nrNormalTex;
    int nrRoughnessTex;
    int nrMetalnessTex;
    sampler2D albedoTex[MAX_SIZE];
    sampler2D specularTex[MAX_SIZE];
    sampler2D normalTex[MAX_SIZE];
    sampler2D roughnessTex[MAX_SIZE];
    sampler2D metalnessTex[MAX_SIZE];
    vec3 albedo;
    vec3 specular;
    float metalness;
    float roughness;

    bool isLight;

    /// Linearly Transformed Cosines corresponding to the Material's BRDF
    /// (see https://drive.google.com/file/d/0BzvWIdpUpRx_d09ndGVjNVJzZjA/view)
    sampler2D ltc1;
    sampler2D ltc2;
};

struct DefaultMaterial {
    vec3 albedo;
    vec3 specular;
    float metalness;
    float roughness;
} defaultMat;

vec2 poissonDisk[16] = vec2[](
vec2( -0.94201624, -0.39906216 ),
vec2( 0.94558609, -0.76890725 ),
vec2( -0.094184101, -0.92938870 ),
vec2( 0.34495938, 0.29387760 ),
vec2( -0.91588581, 0.45771432 ),
vec2( -0.81544232, -0.87912464 ),
vec2( -0.38277543, 0.27676845 ),
vec2( 0.97484398, 0.75648379 ),
vec2( 0.44323325, -0.97511554 ),
vec2( 0.53742981, -0.47373420 ),
vec2( -0.26496911, -0.41893023 ),
vec2( 0.79197514, 0.19090188 ),
vec2( -0.24188840, 0.99706507 ),
vec2( -0.81409955, 0.91437590 ),
vec2( 0.19984126, 0.78641367 ),
vec2( 0.14383161, -0.14100790 )
);

uniform vec3 viewPos;

uniform PointLight pointLights[MAX_SIZE];
uniform int nrPointLights;

uniform DirLight dirLights[MAX_SIZE];
uniform int nrDirLights;

uniform SpotLight spotLights[MAX_SIZE];
uniform int nrSpotLights;

uniform QuadLight quadLights[MAX_SIZE];
uniform int nrQuadLights;

uniform Material material;

uniform bool instantToneMapping;

const float PI = 3.14159265359;

/// basic lighting
float distributionGGX(vec3 N, vec3 H, float r);
float geometrySmith(vec3 N, vec3 V, vec3 L, float r);
vec3 fresnelSchlick(float cosTheta, vec3 F0);

vec3 calcLight(vec3 lightDir, vec3 halfwayDir, vec3 radiance);
vec3 calcPointLight(PointLight light);
vec3 calcDirLight(DirLight light);
vec3 calcSpotLight(SpotLight light);

/// area lighting (using LTC -> https://drive.google.com/file/d/0BzvWIdpUpRx_d09ndGVjNVJzZjA/view)


void getObjectMaterial(Material mat);

float calculateShadow(Shadow shadowData);
float random(vec4 seed4);

vec3 viewDir;
vec3 normal;

void main() {
    normal = normalize(fragNormal);
    viewDir = normalize(viewPos - fragPos);
    getObjectMaterial(material);

    vec3 resultColor = vec3(0.0);

    if (material.isLight)
        resultColor = defaultMat.albedo * defaultMat.specular.r; /// light intensity as the specular color
    else {
        for (int i = 0; i < nrPointLights; ++i) {
            resultColor += calcPointLight(pointLights[i]);
        }
        for (int i = 0; i < nrDirLights; ++i) {
            resultColor += calcDirLight(dirLights[i]);
        }
        for (int i = 0; i < nrSpotLights; ++i) {
            resultColor += calcSpotLight(spotLights[i]);
        }
    }

    vec3 ambient = vec3(0.2) * defaultMat.albedo;
    vec3 color = ambient + resultColor;
    if (instantToneMapping && !material.isLight) {
        color = color / (color + vec3(1.0));;
        color = pow(color, vec3(1.0 / 2.2));
    }
    fragColor = vec4(color, 1.0);
}

float distributionGGX(vec3 N, vec3 H, float r){
    float NdotH = max(dot(N, H), 0.0);
    float a = NdotH * r;
    float k = r / (1.0 - NdotH * NdotH + a * a);
    return k * k * (1.0 / PI);
}

float geometrySmith(vec3 N, vec3 V, vec3 L, float r) {
    float NdotV = max(dot(N, V), 0.0) + 1e-5;
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = NdotL * (NdotV * (1.0 - r) + r);
    float ggx1 = NdotV * (NdotL * (1.0 - r) + r);
    return 0.5 / (ggx1 + ggx2);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    float f = pow(1.0 - cosTheta, 5.0);
    return f + F0 * (1.0 - f);
}

vec3 calcLight(vec3 lightDir, vec3 halfwayDir, vec3 radiance) {
    float D = distributionGGX(normal, halfwayDir, defaultMat.roughness);
    float V = geometrySmith(normal, viewDir, lightDir, defaultMat.roughness);
    vec3 F0 = mix(vec3(0.04), defaultMat.albedo, defaultMat.metalness);
    vec3 F = fresnelSchlick(max(dot(halfwayDir, viewDir), 0.0), F0);

    vec3 kS = (D * V) * F;
    vec3 kD = material.albedo / PI;
    kD *= (1.0 - material.metalness);

    float NdotL = max(dot(normal, lightDir), 0.0);

    return (kS + kD) * radiance * NdotL;
}

vec3 calcPointLight(PointLight light) {
    vec3 lightDir = normalize(light.position - fragPos);
    if (material.nrNormalTex > 0)
        lightDir = normalize(tbn * lightDir);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float distance = length(light.position - fragPos);
    float attenuation = light.intensity / (distance * distance);
    vec3 radiance = light.color * attenuation;

    //float shadowValue = 1.0 - calculateShadow(light.shadowData);
    return calcLight(lightDir, halfwayDir, radiance);// * shadowValue;
}

vec3 calcDirLight(DirLight light){
    vec3 lightDir = normalize(-light.direction);
    if (material.nrNormalTex > 0)
        lightDir = normalize(tbn * lightDir);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec3 radiance = light.color;

    float shadowValue = 1.0 - calculateShadow(light.shadowData);
    return calcLight(lightDir, halfwayDir, radiance) * shadowValue;
}

vec3 calcSpotLight(SpotLight light) {
    vec3 lightDir = normalize(light.position - fragPos);
    if (material.nrNormalTex > 0)
        lightDir = normalize(tbn * lightDir);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float distance = length(light.position - fragPos);
    float attenuation = light.intensity / (distance * distance);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 radiance = light.color * attenuation * intensity;

    float shadowValue = 1.0 - calculateShadow(light.shadowData);
    return calcLight(lightDir, halfwayDir, radiance) * shadowValue;
}

void getObjectMaterial(Material mat) {
    defaultMat.albedo = mat.albedo;
    defaultMat.specular = mat.specular;
    defaultMat.metalness = mat.metalness;
    defaultMat.roughness = mat.roughness;

    if (mat.nrAlbedoTex > 0) {
        defaultMat.albedo = texture2D(mat.albedoTex[0], fragTex).rgb;
    }
    if (mat.nrSpecularTex > 0) {
        defaultMat.specular = vec3(texture2D(mat.specularTex[0], fragTex).r);
    }
    if (mat.nrNormalTex > 0) {
        normal = 2.0 * normalize(texture2D(mat.normalTex[0], fragTex).rgb) - 1.0;
        viewDir = normalize(tbn * viewDir);
    }
    if (mat.nrRoughnessTex > 0) {
        defaultMat.roughness = texture2D(mat.roughnessTex[0], fragTex).r;
    }
    if (mat.nrMetalnessTex > 0) {
        defaultMat.metalness = texture2D(mat.metalnessTex[0], fragTex).r;
    }
}

float calculateShadow(Shadow shadowData) {
    vec4 fragPosLightSpace = shadowData.lightSpaceMatrix * vec4(fragPos, 1.0);
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float currentDepth = projCoords.z;
    float eps = 5e-3;
    if (currentDepth > 1.0 - eps) return 0.0;
    // PCF
    float shadowValue = 0.0;
    vec2 texSize = textureSize(shadowData.shadowMap, 0);
    vec2 texelSize = 1.0 / texSize;
    int nrSample = 0;
    int nrPoisson = 4;
    for (int i = -1 ; i <= 1 ; ++i) {
        for (int j = -1 ; j <= 1 ; ++j) {
            vec2 actualCoords = projCoords.xy + vec2(i, j) * texelSize;
            for (int k = 0 ; k < nrPoisson ; ++k) {
                int index = int(16.0 * random(vec4(floor(fragPos.xyz * 1000.0), k))) % 16;
                float depth = texture2D(shadowData.shadowMap, actualCoords + poissonDisk[index] / 700.0).r;
                float strength = 0.9;//1.0 - clamp(4.0 * pow(currentDepth - depth, 2.0), 0.0, 1.0);
                shadowValue += currentDepth - eps > depth ? (1.0 / nrPoisson) * strength : 0.0;
            }
            nrSample++;
        }
    }

    return shadowValue / nrSample;
}

float random(vec4 seed4) {
    float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
    return fract(sin(dot_product) * 43758.5453);
}