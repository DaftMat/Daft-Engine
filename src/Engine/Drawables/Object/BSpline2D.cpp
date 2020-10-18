//
// Created by mathis on 18/10/2020.
//
#include "BSpline2D.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int BSpline2D::m_nrBSpline2D{0};

BSpline2D::BSpline2D(const std::vector<std::vector<glm::vec3>> &controlPoints, int base, float steps, Composite *parent,
                     std::string name)
    : Object(parent, std::move(name)), m_spline{controlPoints, base}, m_steps{steps} {
    create2DBSpline();
}

void BSpline2D::renderEdges(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    /// draw control polygons
    shader.setVec3("color", {0.f, 0.f, 1.f});
    m_meshObjects[1].prepare();
    m_meshObjects[1].render(GL_LINES);
    m_meshObjects[1].unbind();

    /// draw points
    if (selected()) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        shader.setVec3("color", glm::vec3{0.8f});
        m_meshObjects[1].prepare();
        m_meshObjects[1].render(GL_POINTS);
        m_meshObjects[1].unbind();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    /// draw resulting mesh's wireframe
    shader.setVec3("color", glm::vec3{1.f});
    if (selected()) shader.setVec3("color", {1.f, 1.f, 0.f});
    m_meshObjects[0].prepare();
    m_meshObjects[0].render();
    m_meshObjects[0].unbind();
    shader.setVec3("color", glm::vec3{0.f});
}

core::SettingManager BSpline2D::getSettings() const {
    core::SettingManager sm;
    sm.add("Base", m_spline.base());
    sm.add("Steps", m_steps);
    return sm;
}

void BSpline2D::setSettings(const core::SettingManager &s) {
    setBase(s.get<int>("Base"));
    setBase(s.get<float>("Steps"));
}

void BSpline2D::setBase(int b) {
    if (m_spline.base() == b) return;
    m_spline.base() = b;
    updateNextFrame();
}

void BSpline2D::setSteps(float s) {
    if (m_steps == s) return;
    m_steps = s;
    updateNextFrame();
}

void BSpline2D::create2DBSpline() {
    m_spline.resetNodalVectors();

    core::AttribManager am;
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;

    auto nu = m_spline.uNodalVector();
    auto nv = m_spline.vNodalVector();
    float uMin = nu[m_spline.base()], uMax = nu[m_spline.width()];
    float vMin = nv[m_spline.base()], vMax = nv[m_spline.height()];
    float uStep = (uMax - uMin) / m_steps;
    float vStep = (vMax - vMin) / m_steps;

    /// positions + tex coords
    for (float u = uMin; u < uMax; u += uStep) {
        for (float v = vMin; v < vMax; v += vStep) {
            positions.push_back(m_spline.eval(u, v));
            float pi = (u - uMin) / (uMax - uMin);
            float pj = (v - vMin) / (vMax - vMin);
            texCoords.emplace_back(pi, pj);
        }
    }

    /// indices
    int steps = int(m_steps);
    for (int j = 0; j < steps; ++j) {
        for (int i = 0; i < steps; ++i) {
            int index = j + i * steps;
            if (i != steps - 1 && j != steps - 1) {
                am.indices().push_back(index);
                am.indices().push_back(index + steps + 1);
                am.indices().push_back(index + steps);

                am.indices().push_back(index);
                am.indices().push_back(index + 1);
                am.indices().push_back(index + steps + 1);
            }
        }
    }

    /// normals
    for (int y = 0; y < steps; ++y) {
        for (int x = 0; x < steps; ++x) {
            /// add neighbor triangles
            GLuint index = y * steps + x;
            std::vector<GLuint> inds{};
            if (x > 0 && y > 0) {
                inds.push_back(index - steps - 1);
                inds.push_back(index);
                inds.push_back(index - 1);

                inds.push_back(index - steps - 1);
                inds.push_back(index - steps);
                inds.push_back(index);
            }
            if (y > 0 && x < steps - 1) {
                inds.push_back(index - steps);
                inds.push_back(index + 1);
                inds.push_back(index);
            }
            if (x > 0 && y < steps - 1) {
                inds.push_back(index - 1);
                inds.push_back(index);
                inds.push_back(index + steps);
            }
            if (x < steps - 1 && y < steps - 1) {
                inds.push_back(index);
                inds.push_back(index + 1);
                inds.push_back(index + steps + 1);

                inds.push_back(index);
                inds.push_back(index + steps + 1);
                inds.push_back(index + steps);
            }

            /// calculate mean of all neighbor triangles' normals
            glm::vec3 normal{0.f};
            for (int i = 0; i < inds.size(); i += 3) {
                glm::vec<3, GLuint> triangle{inds[i], inds[i + 1], inds[i + 2]};
                if (triangle.x == index) {
                    auto a = glm::normalize(positions[triangle.z] - positions[triangle.x]);
                    auto b = glm::normalize(positions[triangle.y] - positions[triangle.x]);
                    auto triangleNormal = glm::normalize(glm::cross(a, b));
                    normal += triangleNormal;
                } else if (triangle.y == index) {
                    auto a = glm::normalize(positions[triangle.x] - positions[triangle.y]);
                    auto b = glm::normalize(positions[triangle.z] - positions[triangle.y]);
                    auto triangleNormal = glm::normalize(glm::cross(a, b));
                    normal += triangleNormal;
                } else if (triangle.z == index) {
                    auto a = glm::normalize(positions[triangle.y] - positions[triangle.z]);
                    auto b = glm::normalize(positions[triangle.x] - positions[triangle.z]);
                    auto triangleNormal = glm::normalize(glm::cross(a, b));
                    normal += triangleNormal;
                }
            }

            inds.clear();
            normals.push_back(glm::normalize(normal));
        }
    }

    m_meshObjects.clear();

    am.addAttrib(positions);
    am.addAttrib(normals);
    am.addAttrib(texCoords);
    std::vector<core::Mesh> meshes;
    meshes.emplace_back(am);
    m_meshObjects.emplace_back(std::move(meshes));

    meshes.clear();
    for (auto &s : m_spline.USplines()) {
        am.clear();
        am.addAttrib(s.controlPoints());
        for (size_t i = 0; i < s.controlPoints().size() - 1; ++i) {
            am.indices().push_back(i);
            am.indices().push_back(i + 1);
        }
        meshes.emplace_back(am);
    }
    m_meshObjects.emplace_back(std::move(meshes));
}

void BSpline2D::accept(core::DrawableVisitor *visitor) { visitor->visit(this); }
}  // namespace daft::engine