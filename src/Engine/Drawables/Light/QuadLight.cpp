//
// Created by mathis on 28/11/2020.
//
#include "QuadLight.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int QuadLight::m_nrQuadLight{0};

void QuadLight::render(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    shader.setVec3("material.albedo", color());
    shader.setVec3("material.specular", glm::vec3{m_intensity});
    shader.setBool("material.isLight", true);
    m_mesh.prepare();
    m_mesh.render(GL_TRIANGLES);
    m_mesh.unbind();
    shader.setVec3("color", glm::vec3{0.f});
}

core::SettingManager QuadLight::getSettings() const {
    core::SettingManager sm;
    sm.add("Color", color());
    sm.add("Intensity", m_intensity);
    sm.add("Width", m_width);
    sm.add("Height", m_height);
    return sm;
}

void QuadLight::setSettings(const core::SettingManager &s) {
    if (s.has("Color")) color() = s.get<glm::vec3>("Color");
    if (s.has("Intensity")) intensity() = s.get<float>("Intensity");
    if (s.has("Width")) setWidth(s.get<float>("Width"));
    if (s.has("Height")) setHeight(s.get<float>("Height"));
}

void QuadLight::setTransformations(const core::SettingManager &t) {
    position() = t.get<glm::vec3>("Position");
    rotations() = t.get<glm::vec3>("Rotations");
    m_xDir = calculateRotationMat() * glm::vec4(m_xDirBase, 0.f);
    m_yDir = calculateRotationMat() * glm::vec4(m_yDirBase, 0.f);
}

void QuadLight::setWidth(float w) {
    if (w == m_width) return;
    m_width = w;
    updateNextFrame();
}

void QuadLight::setHeight(float h) {
    if (h == m_height) return;
    m_height = h;
    updateNextFrame();
}

void QuadLight::loadToShader(const core::ShaderProgram &shader, int index) const {
    std::string name = "quadLights[" + std::to_string(index) + "]";
    auto p = transformedPoints();
    for (size_t i = 0; i < p.size(); ++i) shader.setVec3(name + ".points[" + std::to_string(i) + "]", p[i]);
    shader.setVec3(name + ".color", color());
    shader.setFloat(name + ".intensity", m_intensity);
}

void QuadLight::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

std::vector<glm::vec3> QuadLight::points() const {
    float halfx = m_width / 2.f;
    float halfy = m_height / 2.f;
    glm::vec3 ex = halfx * m_xDirBase;
    glm::vec3 ey = halfy * m_yDirBase;
    std::vector<glm::vec3> p;
    p.push_back(m_posBase - ex - ey);
    p.push_back(m_posBase + ex - ey);
    p.push_back(m_posBase + ex + ey);
    p.push_back(m_posBase - ex + ey);
    return p;
}

std::vector<glm::vec3> QuadLight::transformedPoints() const {
    std::vector<glm::vec3> ps = points();
    for (auto &p : ps) p = model() * glm::vec4(p, 1.f);
    return ps;
}

void QuadLight::createQuadLight() {
    std::vector<glm::vec3> positions = points();
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords{{0.f, 1.f}, {1.f, 1.f}, {1.f, 0.f}, {0.f, 0.f}};
    std::vector<GLuint> indices{0, 1, 2, 0, 2, 3};

    glm::vec3 normal = glm::cross(m_xDirBase, m_yDirBase);
    for (int i = 0; i < 4; ++i) normals.push_back(normal);

    core::AttribManager am;
    am.addAttrib<glm::vec3>(positions);
    am.addAttrib<glm::vec3>(normals);
    am.addAttrib<glm::vec2>(texCoords);
    am.indices() = indices;

    m_mesh = core::Mesh(am);
}

}  // namespace daft::engine