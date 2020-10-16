//
// Created by mathis on 30/09/2020.
//
#include "SpotLight.hpp"

#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/primitives.hpp>
#include <Engine/Renderer/Cameras/Camera.hpp>

namespace daft::engine {
int SpotLight::m_nrSpotLight{0};

SpotLight::SpotLight(glm::vec3 dir, float intensity, float innerCutOff, float outerCutOff, glm::vec3 color,
                     Composite *parent, std::string name)
    : Light(color, parent, std::move(name)),
      m_direction{dir},
      m_baseDirection{dir},
      m_intensity{intensity},
      m_innerCutOff{innerCutOff},
      m_outerCutOff{outerCutOff} {
    createSpotLight();
}

core::SettingManager SpotLight::getSettings() const {
    core::SettingManager sm{};
    sm.add("Color", color());
    sm.add("Intensity", m_intensity);
    sm.add("Inner angle", m_innerCutOff);
    sm.add("Outer angle", m_outerCutOff);
    return sm;
}

void SpotLight::setSettings(const core::SettingManager &s) {
    color() = s.get<glm::vec3>("Color");
    setIntensity(s.get<float>("Intensity"));
    setInnerCutOff(s.get<float>("Inner angle"));
    setOuterCutOff(s.get<float>("Outer angle"));
}

void SpotLight::setTransformations(const core::SettingManager &t) {
    position() = t.get<glm::vec3>("Position");
    rotations() = t.get<glm::vec3>("Rotations");
    m_direction = calculateRotationMat() * glm::vec4(m_baseDirection, 0);
}

void SpotLight::setIntensity(float i) {
    if (i == m_intensity) return;
    m_intensity = i;
    updateNextFrame();
}

void SpotLight::setInnerCutOff(float i) {
    if (i == m_innerCutOff) return;
    if (i > m_outerCutOff) i = m_outerCutOff;
    m_innerCutOff = i;
    updateNextFrame();
}

void SpotLight::setOuterCutOff(float o) {
    if (o == m_outerCutOff) return;
    if (o < m_innerCutOff) o = m_innerCutOff;
    m_outerCutOff = o;
    updateNextFrame();
}

void SpotLight::loadToShader(const core::ShaderProgram &shader, int index) const {
    std::string name = "spotLights[" + std::to_string(index) + "]";
    shader.setVec3(name + ".position", position());
    shader.setVec3(name + ".direction", m_direction);
    shader.setFloat(name + ".innerCutOff", glm::cos(glm::radians(m_innerCutOff)));
    shader.setFloat(name + ".outerCutOff", glm::cos(glm::radians(m_outerCutOff)));
    shader.setFloat(name + ".intensity", m_intensity);
    shader.setVec3(name + ".color", color());
    shader.setMat4(name + ".shadowData.lightSpaceMatrix", m_lightSpaceMatrix);
}

void SpotLight::renderToLightMap(Composite *root, const core::ShaderProgram &shader, int screenWidth, int screenHeight,
                                 const daft::engine::Camera &viewCam) {
    m_fbo->use();
    glClear(GL_DEPTH_BUFFER_BIT);
    glm::vec3 center = viewCam.target();
    glm::vec3 right = glm::cross(-m_direction, glm::vec3{0.f, 1.f, 0.f});
    glm::vec3 up = glm::cross(right, -m_direction);
    glm::mat4 lightView = glm::lookAt(position(), position() - m_direction, up);
    glm::mat4 lightProj = glm::ortho(-20.f, 20.f, -20.f, 20.f, 1.f, 40.f);
    m_lightSpaceMatrix = lightProj * lightView;
    shader.setMat4("lightSpaceMatrix", m_lightSpaceMatrix);
    root->render(shader);
    m_fbo->stop(screenWidth, screenHeight);
}

void SpotLight::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void SpotLight::createSpotLight() {
    /// initialize position and indices with the star
    auto star = createStar();
    std::vector<glm::vec3> positions = star.getAttribs<glm::vec3>(0)->attribs;
    std::vector<GLuint> indices = star.indices();

    float factor = m_intensity * 4.f;
    float innerDist = glm::tan(glm::radians(m_innerCutOff)) * factor;
    float outerDist = glm::tan(glm::radians(m_outerCutOff)) * factor;
    glm::vec3 target = m_baseDirection * factor;
    int circleSteps = 64;
    int innerOffset = int(positions.size());

    auto innerCircle = createCircle(target, target, innerDist, circleSteps);
    std::vector<glm::vec3> innerCirclePositions = innerCircle.getAttribs<glm::vec3>(0)->attribs;
    auto innerCircleIndices = innerCircle.indices();
    for (auto &index : innerCircleIndices) index += innerOffset;

    int outerOffset = innerOffset + int(innerCirclePositions.size());
    auto outerCircle = createCircle(target, target, outerDist, circleSteps);
    std::vector<glm::vec3> outerCirclePositions = outerCircle.getAttribs<glm::vec3>(0)->attribs;
    auto outerCircleIndices = outerCircle.indices();
    for (auto &index : outerCircleIndices) index += GLuint(outerOffset);

    /// add the circles to positions and indices
    for (auto pos : innerCirclePositions) positions.push_back(pos);
    for (auto index : innerCircleIndices) indices.push_back(index);
    for (auto pos : outerCirclePositions) positions.push_back(pos);
    for (auto index : outerCircleIndices) indices.push_back(index);

    /// link circles/star together
    for (int i = 0; i < 4; ++i) {
        int index = (i * circleSteps) / 2;
        indices.push_back(0);
        indices.push_back(innerCircleIndices[index]);

        indices.push_back(0);
        indices.push_back(outerCircleIndices[index]);

        indices.push_back(innerCircleIndices[index]);
        indices.push_back(outerCircleIndices[index]);
    }

    core::AttribManager am{};
    am.addAttrib(positions);
    am.indices() = indices;

    m_mesh = Mesh{am};
}
}  // namespace daft::engine