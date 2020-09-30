//
// Created by mathis on 11/09/2020.
//
#include "PointLight.hpp"

#include <Engine/Drawables/Object/primitives.hpp>

namespace daft::engine {
int PointLight::m_nrPointLights{0};

PointLight::PointLight(float intensity, glm::vec3 color, daft::engine::Composite *parent, std::string name)
    : Light(color, parent, std::move(name)), m_intensity{intensity} {
    createPointLight();
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
}

void PointLight::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void PointLight::createPointLight() {
    std::vector<glm::vec3> dir{
        {0.f, 0.f, 1.f},   // front
        {0.f, 0.f, -1.f},  // back
        {0.f, 1.f, 0.f},   // top
        {0.f, -1.f, 0.f},  // bottom
        {1.f, 0.f, 0.f},   // right
        {-1.f, 0.f, 0.f}   // left
    };

    core::AttribManager am;
    std::vector<glm::vec3> positions;
    positions.emplace_back(0.f);

    for (size_t i = 0; i < dir.size(); ++i) {
        positions.push_back(dir[i] * 0.5f);
        am.indices().push_back(0);
        am.indices().push_back(i + 1);
    }

    am.addAttrib(positions);

    m_mesh = Mesh{createCircle(position(), glm::vec3{0.f, 1.f, 0.f}, m_intensity)};
}

void PointLight::setTransformations(const core::SettingManager &t) { position() = t.get<glm::vec3>("Position"); }
}  // namespace daft::engine