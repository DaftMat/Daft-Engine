//
// Created by mathis on 03/10/2020.
//
#include "DirLight.hpp"

#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/primitives.hpp>

namespace daft::engine {
int DirLight::m_nrDirLight{0};

DirLight::DirLight(glm::vec3 dir, glm::vec3 color, Composite *parent, std::string name)
    : Light(color, parent, std::move(name)), m_direction{dir}, m_baseDirection{dir} {
    createDirLight();
    m_shadowMap.id() = m_fbo->textures()[0];
}

core::SettingManager DirLight::getSettings() const {
    core::SettingManager sm;
    sm.add("Color", color() * 255.f);
    return sm;
}

void DirLight::setSettings(const core::SettingManager &s) { color() = s.get<glm::vec3>("Color") / 255.f; }

void DirLight::setTransformations(const core::SettingManager &t) {
    rotations() = t.get<glm::vec3>("Rotations");
    m_direction = calculateRotationMat() * glm::vec4(m_baseDirection, 0);
}

void DirLight::loadToShader(const core::ShaderProgram &shader, int index) const {
    std::string name = "dirLights[" + std::to_string(index) + "]";
    shader.setVec3(name + ".direction", m_direction);
    shader.setVec3(name + ".color", color());
    shader.setMat4(name + ".lightSpaceMatrix", m_lightSpaceMatrix);
}

void DirLight::renderToLightMap(Composite *root, const core::ShaderProgram &shader, int screenWidth, int screenHeight,
                                const Camera &viewCam) {
    m_fbo->use();
    glClear(GL_DEPTH_BUFFER_BIT);
    glm::vec3 center = viewCam.target();
    float dist = glm::length(viewCam.target() - viewCam.position()) * 1.6f;
    glm::vec3 cameraPos = center - m_direction * 10.f;
    glm::vec3 right = glm::cross(m_direction, glm::vec3{0.f, 1.f, 0.f});
    glm::vec3 up = glm::cross(right, m_direction);
    glm::mat4 lightView = glm::lookAt(cameraPos, cameraPos + m_direction, up);
    glm::mat4 lightProj = glm::ortho(-dist, dist, -dist, dist, 1.f, 40.f);
    m_lightSpaceMatrix = lightProj * lightView;
    shader.setMat4("lightSpaceMatrix", m_lightSpaceMatrix);
    root->render(shader);
    m_fbo->stop(screenWidth, screenHeight);
}

void DirLight::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void DirLight::createDirLight() {
    glm::vec3 circlePos = -m_baseDirection * 2.f;
    float radius = 0.2f;
    int steps = 64;

    std::vector<glm::vec3> positions;
    positions.emplace_back(0.f);
    positions.push_back(circlePos);
    std::vector<GLuint> indices{0, 1};
    int offset = positions.size();

    auto circleAm = createCircle(circlePos, m_baseDirection, radius, steps);
    std::vector<glm::vec3> circlePositions = circleAm.getAttribs<glm::vec3>(0)->attribs;
    std::vector<GLuint> circleIndices = circleAm.indices();
    for (auto &index : circleIndices) index += GLuint(offset);

    for (auto pos : circlePositions) positions.push_back(pos);
    for (auto index : circleIndices) indices.push_back(index);

    for (int i = 0; i < 4; ++i) {
        auto index = offset + (i * steps) / 4;
        indices.push_back(0);
        indices.push_back(index);
        indices.push_back(1);
        indices.push_back(index);
    }

    core::AttribManager am{};
    am.addAttrib(positions);
    am.indices() = indices;

    m_mesh = Mesh{am};
}
}  // namespace daft::engine