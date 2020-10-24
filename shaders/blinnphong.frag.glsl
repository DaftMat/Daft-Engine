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
};

struct DefaultMaterial {
    vec3 albedo;
    vec3 specular;
    float shininess;
    float reflectivity;
} defaultMat;

uniform vec3 viewPos;

uniform PointLight pointLights[MAX_SIZE];
uniform int nrPointLights;

uniform DirLight dirLights[MAX_SIZE];
uniform int nrDirLights;

uniform SpotLight spotLights[MAX_SIZE];
uniform int nrSpotLights;

uniform Material material;

uniform bool instantToneMapping;

vec3 calcPointLight(PointLight light);
vec3 calcDirLight(DirLight light);
vec3 calcSpotLight(SpotLight light);

float calculateShadow(Shadow shadowData);

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
    for (int i = 0 ; i < nrPointLights ; ++i) {
        resultColor += calcPointLight(pointLights[i]);
    }
    for (int i = 0 ; i < nrDirLights ; ++i) {
        resultColor += calcDirLight(dirLights[i]);
    }
    for (int i = 0 ; i < nrSpotLights ; ++i) {
        resultColor += calcSpotLight(spotLights[i]);
    }

    vec3 ambient = vec3(0.03) * defaultMat.albedo;
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
    //if (currentDepth > 1.0 - eps) return 0.0;
    // PCF
    float shadowValue = 0.0;
    vec2 texSize = textureSize(shadowData.shadowMap, 0);
    vec2 texelSize = 1.0 / texSize;
    int nrSample = 0;
    for (int i = -3 ; i <= 3 ; ++i) {
        for (int j = -3 ; j <= 3 ; ++j) {
            vec2 actualCoords = projCoords.xy + vec2(i, j) * texelSize;
            float depth = texture2D(shadowData.shadowMap, actualCoords).r;
            shadowValue += currentDepth - eps > depth ? 1.0 : 0.0;
            nrSample++;
        }
    }
    return shadowValue / nrSample;
}