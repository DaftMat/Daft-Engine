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
    vec3 color;
};

struct Material {
    int nrAlbedoTex;
    int nrSpecularTex;
    int nrNormalTex;
    int nrReflectionTex;
    sampler2D albedoTex[MAX_SIZE];
    sampler2D specularTex[MAX_SIZE];
    sampler2D normalTex[MAX_SIZE];
    sampler2D reflectionTex[MAX_SIZE];
    vec3 albedo;
    vec3 specular;
    float shininess;
    float reflectivity;

    bool isLight;
};

struct DefaultMaterial {
    vec3 albedo;
    vec3 specular;
    float shininess;
    float reflectivity;
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

vec3 calcPointLight(PointLight light);
vec3 calcDirLight(DirLight light);
vec3 calcSpotLight(SpotLight light);

float calculateShadow(Shadow shadowData);
float random(vec4 seed4);

vec3 viewDir;
vec3 normal;

void main() {
    defaultMat.albedo = material.albedo;
    defaultMat.specular = material.specular;
    defaultMat.shininess = material.shininess;
    defaultMat.reflectivity = material.reflectivity;
    normal = normalize(fragNormal);
    viewDir = normalize(viewPos - fragPos);

    if (material.nrAlbedoTex > 0) {
        defaultMat.albedo = texture2D(material.albedoTex[0], fragTex).rgb;
    }
    if (material.nrSpecularTex > 0) {
        defaultMat.specular = vec3(texture2D(material.specularTex[0], fragTex).r);
    }
    if (material.nrNormalTex > 0) {
        normal = 2.0 * normalize(texture2D(material.normalTex[0], fragTex).rgb) - 1.0;
        viewDir = normalize(tbn * viewDir);
    }
    if (material.nrReflectionTex > 0) {
        defaultMat.reflectivity = texture2D(material.reflectionTex[0], fragTex).r;
    }

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
        for (int i = 0; i < nrQuadLights; ++i) {
            PointLight pl;
            pl.position = vec3(0.f);
            for (int j = 0 ; j < 4 ; ++j)
                pl.position += quadLights[i].points[j];
            pl.position /= 4.0;
            pl.intensity = quadLights[i].intensity;
            pl.color = quadLights[i].color;
            resultColor += calcPointLight(pl);
        }
    }

    vec3 ambient = vec3(0.2) * defaultMat.albedo;
    vec3 color = ambient + resultColor;
    if (instantToneMapping) {
        color = color / (color + vec3(1.0));;
        color = pow(color, vec3(1.0 / 2.2));
    }
    fragColor = vec4(color, 1.0);
}

vec3 calcPointLight(PointLight light) {
    vec3 lightDir = normalize(light.position - fragPos);
    if (material.nrNormalTex > 0)
        lightDir = normalize(tbn * lightDir);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), defaultMat.shininess);
    float distance = length(light.position - fragPos);
    float attenuation = light.intensity / (distance * distance);
    vec3 diffuse = light.color * diff * defaultMat.albedo * attenuation;
    vec3 specular = light.color * spec * defaultMat.specular * attenuation * defaultMat.reflectivity;
    //float shadowValue = 1.0 - calculateShadow(light.shadowData);
    return (diffuse + specular);// * shadowValue;
}

vec3 calcDirLight(DirLight light){
    vec3 lightDir = normalize(-light.direction);
    if (material.nrNormalTex > 0)
        lightDir = normalize(tbn * lightDir);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), defaultMat.shininess);
    vec3 diffuse = light.color * diff * defaultMat.albedo;
    vec3 specular = light.color * spec * defaultMat.specular * defaultMat.reflectivity;
    float shadowValue = 1.0 - calculateShadow(light.shadowData);
    return shadowValue * (diffuse + specular);
}

vec3 calcSpotLight(SpotLight light) {
    vec3 lightDir = normalize(light.position - fragPos);
    if (material.nrNormalTex > 0)
        lightDir = normalize(tbn * lightDir);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), defaultMat.shininess);
    float distance = length(light.position - fragPos);
    float attenuation = light.intensity / (distance * distance);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 diffuse = light.color * diff * defaultMat.albedo;
    vec3 specular = light.color * spec * defaultMat.specular * defaultMat.reflectivity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    float shadowValue = 1.0 - calculateShadow(light.shadowData);
    return shadowValue * (diffuse + specular);
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