//
// Created by mathis on 10/09/2020.
//
#include "Torus.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int Torus::m_nrTorus{0};

Torus::Torus(int meridians, int parallels, float innerRadius, float outerRadius, Composite *parent, std::string name)
    : Object(parent, std::move(name)),
      m_meridians{meridians},
      m_parallels{parallels},
      m_innerRadius{innerRadius},
      m_outerRadius{outerRadius} {
    createTorus();
}

core::SettingManager Torus::getSettings() const {
    core::SettingManager sm;
    sm.add("Meridians", m_meridians);
    sm.add("Parallels", m_parallels);
    sm.add("Inner Radius", m_innerRadius);
    sm.add("Outer Radius", m_outerRadius);
    return sm;
}

void Torus::setSettings(const core::SettingManager &s) {
    if (s.has("Meridians")) setMeridians(s.get<int>("Meridians"));
    if (s.has("Parallels")) setParallels(s.get<int>("Parallels"));
    if (s.has("Inner Radius")) setInnerRadius(s.get<float>("Inner Radius"));
    if (s.has("Outer Radius")) setOuterRadius(s.get<float>("Outer Radius"));
}

void Torus::setMeridians(int m) {
    if (m_meridians == m) return;
    m_meridians = m;
    updateNextFrame();
}

void Torus::setParallels(int p) {
    if (m_parallels == p) return;
    m_parallels = p;
    updateNextFrame();
}

void Torus::setInnerRadius(float r) {
    if (m_innerRadius == r) return;
    m_innerRadius = r;
    updateNextFrame();
}

void Torus::setOuterRadius(float r) {
    if (m_outerRadius == r) return;
    m_outerRadius = r;
    updateNextFrame();
}

void Torus::createTorus() {
    core::AttribManager am;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> tangents;

    float mStep = (2.f * glm::pi<float>()) / float(m_meridians);
    float pStep = (2.f * glm::pi<float>()) / float(m_parallels);

    for (int j = 0; j <= m_meridians; ++j) {
        float mAngle = float(j) * mStep;
        for (int i = 0; i <= m_parallels; ++i) {
            float pAngle = float(i) * pStep;
            glm::vec3 outCenter = m_innerRadius * glm::vec3{glm::cos(mAngle), 0.f, glm::sin(mAngle)};

            auto w = glm::normalize(outCenter);
            glm::vec3 pos = outCenter + m_outerRadius * glm::cos(pAngle) * w +
                            m_outerRadius * glm::sin(pAngle) * glm::vec3{0.f, 1.f, 0.f};

            positions.push_back(pos);
            glm::vec3 n = glm::normalize(pos - outCenter);
            normals.push_back(n);
            texCoords.emplace_back(mAngle, pAngle);
            glm::vec3 t, b;
            core::orthoVectors(n, t, b);
            tangents.push_back(t);
        }
    }
    am.addAttrib(positions);
    am.addAttrib(normals);
    am.addAttrib(texCoords);

    /// topology
    for (int i = 1; i <= m_meridians; ++i) {
        for (int j = 0; j < m_parallels; ++j) {
            int max = m_parallels + 1;
            /// first triangle
            am.indices().push_back(j + max * i);
            am.indices().push_back((j + 1) + max * i);
            am.indices().push_back(j + max * (i - 1));
            /// second triangle
            am.indices().push_back(j + max * (i - 1));
            am.indices().push_back((j + 1) + max * i);
            am.indices().push_back((j + 1) + max * (i - 1));
        }
    }

    m_meshObjects.clear();
    std::vector<core::Mesh> meshes;
    meshes.emplace_back(am);
    m_meshObjects.emplace_back(std::move(meshes));
}

void Torus::accept(core::DrawableVisitor *visitor) { visitor->visit(this); }
}  // namespace daft::engine