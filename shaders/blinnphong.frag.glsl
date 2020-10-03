#version 450
layout (location = 0) out vec4 fragColor;

struct Material {
    vec3 albedo;
    vec3 specular;
    float shininess;
} defaultMat;

struct PointLight {
    vec3 position;
    float intensity;
    vec3 color;
};

struct DirLight {
    vec3 direction;
    vec3 color;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;
    float intensity;
    vec3 color;
};

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTex;

#define MAX_LIGHTS 32

uniform vec3 viewPos;

uniform PointLight pointLights[MAX_LIGHTS];
uniform int nrPointLights;

uniform DirLight dirLights[MAX_LIGHTS];
uniform int nrDirLights;

uniform SpotLight spotLights[MAX_LIGHTS];
uniform int nrSpotLights;

vec3 calcPointLight(PointLight light);
vec3 calcDirLight(DirLight light);
vec3 calcSpotLight(SpotLight light);

vec3 viewDir;

void main() {
    defaultMat.albedo = vec3(0.6);
    defaultMat.specular = vec3(1.0);
    defaultMat.shininess = 3.0;

    viewDir = normalize(viewPos - fragPos);
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
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.4));
    fragColor = vec4(color, 1.0);
}

vec3 calcPointLight(PointLight light) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(fragNormal, halfwayDir), 0.0), defaultMat.shininess);
    float distance = length(light.position - fragPos);
    float attenuation = light.intensity / (distance * distance);
    vec3 diffuse = light.color * diff * vec3(defaultMat.albedo) * attenuation;
    vec3 specular = light.color * spec * vec3(defaultMat.specular) * attenuation;
    return diffuse + specular;
}

vec3 calcDirLight(DirLight light){
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(fragNormal, halfwayDir), 0.0), defaultMat.shininess);
    vec3 diffuse = light.color * diff * vec3(defaultMat.albedo);
    vec3 specular = light.color * spec * vec3(defaultMat.specular);
    return diffuse + specular;
}

vec3 calcSpotLight(SpotLight light) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(fragNormal, halfwayDir), 0.0), defaultMat.shininess);
    float distance = length(light.position - fragPos);
    float attenuation = light.intensity / (distance * distance);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 diffuse = light.color * diff * vec3(defaultMat.albedo);
    vec3 specular = light.color * spec * vec3(defaultMat.specular);
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return diffuse + specular;
}
