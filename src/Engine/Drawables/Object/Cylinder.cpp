//
// Created by mathis on 05/10/2020.
//
#include "Cylinder.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

#include "primitives.hpp"

namespace daft::engine {
int Cylinder::m_nrCylinder{0};

Cylinder::Cylinder(int meridians, int parallels, float radius, daft::engine::Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_meridians{meridians}, m_parallels{parallels}, m_radius{radius} {
    createCylinder();
}

core::SettingManager Cylinder::getSettings() const {
    core::SettingManager sm;
    sm.add("Meridians", m_meridians);
    sm.add("Parallels", m_parallels);
    sm.add("Radius", m_radius);
    return sm;
}

void Cylinder::setSettings(const core::SettingManager &s) {
    if (s.has("Meridians")) setMeridians(s.get<int>("Meridians"));
    if (s.has("Parallels")) setParallels(s.get<int>("Parallels"));
    if (s.has("Radius")) setRadius(s.get<float>("Radius"));
}

void Cylinder::setMeridians(int m) {
    if (m_meridians == m) return;
    m_meridians = m;
    updateNextFrame();
}

void Cylinder::setParallels(int p) {
    if (m_parallels == p) return;
    m_parallels = p;
    updateNextFrame();
}

void Cylinder::setRadius(float r) {
    if (m_radius == r) return;
    m_radius = r;
    updateNextFrame();
}

void Cylinder::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void Cylinder::createCylinder() {
    std::vector<glm::vec3> positions{};
    std::vector<glm::vec3> normals{};
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> tangents;
    std::vector<GLuint> indices{};

    glm::vec3 northPole{0.f, 1.f, 0.f};
    glm::vec3 southPole{0.f, -1.f, 0.f};
    float step = circleStep(m_meridians);

    for (int i = 0; i <= m_meridians + 1; ++i) {
        float theta = step * float(i);
        glm::vec3 circleDir = glm::normalize(glm::vec3{glm::cos(theta), 0.f, glm::sin(theta)});
        for (int j = 0; j <= m_parallels; ++j) {
            glm::vec3 center = core::lerp(northPole, southPole, float(j) / float(m_parallels));

            positions.push_back(center + circleDir * m_radius);
            normals.push_back(circleDir);
            glm::vec3 t, b;
            core::orthoVectors(circleDir, t, b);
            tangents.push_back(t);
        }
    }

    for (int i = 1; i <= m_meridians; ++i) {
        for (int j = 0; j < m_parallels; ++j) {
            int max = m_parallels + 1;
            /// first triangle
            indices.push_back(j + max * i);
            indices.push_back((j + 1) + max * i);
            indices.push_back(j + max * (i - 1));
            /// second triangle
            indices.push_back(j + max * (i - 1));
            indices.push_back((j + 1) + max * i);
            indices.push_back((j + 1) + max * (i - 1));
        }
    }

    createDisk(northPole, positions, normals, tangents, indices);
    createDisk(southPole, positions, normals, tangents, indices);

    core::AttribManager am{};
    am.addAttrib(positions);
    am.addAttrib(normals);
    am.addAttrib(texCoords);
    am.addAttrib(tangents);
    am.indices() = indices;

    m_meshObjects.clear();
    std::vector<core::Mesh> meshes;
    meshes.emplace_back(am);
    m_meshObjects.emplace_back(std::move(meshes));
}

void Cylinder::createDisk(glm::vec3 pole, std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals,
                          std::vector<glm::vec3> &tangents, std::vector<GLuint> &indices) const {
    GLuint startIndex = positions.size();
    GLuint index = startIndex + 1;
    positions.push_back(pole);
    normals.push_back(pole);
    glm::vec3 t, b;
    core::orthoVectors(pole, t, b);
    tangents.push_back(t);
    auto step = circleStep(m_meridians);
    for (int i = 0; i <= m_meridians; ++i) {
        float theta = step * float(i);
        glm::vec3 circleDir = glm::normalize(glm::vec3{glm::cos(theta), 0.f, glm::sin(theta)});
        positions.push_back(pole + circleDir * m_radius);
        normals.push_back(pole);
        tangents.push_back(t);

        if (i > 0) {
            indices.push_back(startIndex);
            indices.push_back(index - 1);
            indices.push_back(index);
        }
        index++;
    }
}
}  // namespace daft::engine