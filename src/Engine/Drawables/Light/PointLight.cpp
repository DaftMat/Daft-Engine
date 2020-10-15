//
// Created by mathis on 11/09/2020.
//
#include "PointLight.hpp"

#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/Object/primitives.hpp>
#include <Engine/Renderer/Cameras/Camera.hpp>

namespace daft::engine {
int PointLight::m_nrPointLights{0};

PointLight::PointLight(float intensity, glm::vec3 color, daft::engine::Composite *parent, std::string name)
    : Light(color, parent, std::move(name)), m_intensity{intensity} {
    createPointLight();
    m_shadowMap.id() = m_fbo->textures()[0];
}

core::SettingManager PointLight::getSettings() const {
    core::SettingManager sm;
    sm.add("Color", color() * 255.f);
    sm.add("Intensity", m_intensity);
    return sm;
}

void PointLight::setSettings(const core::SettingManager &s) {
    color() = s.get<glm::vec3>("Color") / 255.f;
    m_intensity = s.get<float>("Intensity");
}

void PointLight::loadToShader(const core::ShaderProgram &shader, int index) const {
    std::string name = "pointLights[" + std::to_string(index) + "]";
    shader.setVec3(name + ".position", position());
    shader.setVec3(name + ".color", color());
    shader.setFloat(name + ".intensity", m_intensity);
    shader.setMat4(name + ".lightSpaceMatrix", m_lightSpaceMatrix);
}

void PointLight::renderToLightMap(Composite *root, const core::ShaderProgram &shader, int screenWidth, int screenHeight,
                                  const daft::engine::Camera &viewCam) {
    m_fbo->use();
    glClear(GL_DEPTH_BUFFER_BIT);
    glm::vec3 center = viewCam.target();
    glm::vec3 lightToCenter = center - position();
    glm::vec3 right = glm::cross(glm::normalize(lightToCenter), glm::vec3{0.f, 1.f, 0.f});
    glm::vec3 up = glm::cross(right, glm::normalize(lightToCenter));
    glm::mat4 lightView = glm::lookAt(position(), position() + glm::normalize(lightToCenter), up);
    glm::mat4 lightProj = glm::ortho(-20.f, 20.f, -20.f, 20.f, 1.f, 2.f * glm::length(lightToCenter));
    m_lightSpaceMatrix = lightProj * lightView;
    shader.setMat4("lightSpaceMatrix", m_lightSpaceMatrix);
    root->render(shader);
    m_fbo->stop(screenWidth, screenHeight);
}

void PointLight::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void PointLight::createPointLight() { m_mesh = Mesh{createStar(position())}; }

void PointLight::setTransformations(const core::SettingManager &t) { position() = t.get<glm::vec3>("Position"); }
}  // namespace daft::engine