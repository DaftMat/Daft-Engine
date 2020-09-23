//
// Created by daftmat on 23/09/2020.
//

#include "BSpline.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int BSpline::m_nrBSpline{0};

BSpline::BSpline(std::vector<glm::vec3> controlPoints, int base, float steps, Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_controlPoints{std::move(controlPoints)}, m_base{base}, m_steps{steps} {
    for (int i = 0; i < m_base + int(m_controlPoints.size()) + 1; ++i) m_modalVector.push_back(float(i));
    createBSpline();
}

void BSpline::renderEdges(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    shader.setVec3("color", {0.f, 0.f, 1.f});
    m_meshObjects[1].prepare();
    m_meshObjects[1].render(GL_LINES);
    m_meshObjects[1].unbind();
    shader.setVec3("color", glm::vec3{1.f});
    if (selected()) shader.setVec3("color", {1.f, 1.f, 0.f});
    m_meshObjects[0].prepare();
    m_meshObjects[0].render(GL_LINES);
    m_meshObjects[0].unbind();
    shader.setVec3("color", glm::vec3{0.f});
}

void BSpline::createBSpline() {
    m_meshObjects.clear();
    /// from:   m_modalVector[m_base]
    /// to:     m_modalVector[m_modalVector.size()]
    core::AttribManager am{};
    std::vector<glm::vec3> positions;
    int index = 0;
    float umin = m_modalVector[m_base];
    float umax = m_modalVector[m_controlPoints.size()];
    for (float u = umin; u < umax; u += (umax - umin) / m_steps) {
        if (index > 0) {
            am.indices().push_back(index - 1);
            am.indices().push_back(index++);
        } else
            index++;
        positions.push_back(eval(u));
    }
    am.addAttrib(positions);
    m_meshObjects.emplace_back(core::Mesh{am});

    /// control polygon to display
    am.clear();
    am.addAttrib(m_controlPoints);
    for (size_t i = 0; i < m_controlPoints.size() - 1; ++i) {
        am.indices().push_back(i);
        am.indices().push_back(i + 1);
    }
    m_meshObjects.emplace_back(core::Mesh{am});
}

core::SettingManager BSpline::getSettings() const {
    core::SettingManager sm;
    sm.add("Base", m_base);
    sm.add("Steps", m_steps);
    return sm;
}

void BSpline::setSettings(const core::SettingManager &s) {
    setBase(s.get<int>("Base"));
    setSteps(s.get<float>("Steps"));
}

void BSpline::setBase(int b) {
    if (m_base == b) return;
    m_base = b;
    updateNextFrame();
}

void BSpline::setSteps(float s) {
    if (m_steps == s) return;
    m_steps = s;
    updateNextFrame();
}

glm::vec3 BSpline::eval(float u) const {
    /// find pTemp
    int k = m_base + 1;
    int dec = 0, i = k;
    while (u > m_modalVector[i++]) dec++;

    std::vector<glm::vec3> pTemp;
    for (int j = dec; j < dec + k; ++j) pTemp.push_back(m_controlPoints[j]);

    /// calculate B-Spline point at u
    for (int h = 0; h < m_base; ++h) {
        for (int j = 0; j < k - 1; ++j) {
            float u1 = m_modalVector[dec + k + j];
            float u2 = m_modalVector[dec + 1 + j];
            float div = u1 - u2;
            pTemp[j] = (u1 - u) / div * pTemp[j] + (u - u2) / div * pTemp[j + 1];
        }
        ++dec;
        --k;
    }
    return pTemp[0];
}

void BSpline::accept(core::DrawableVisitor *visitor) { visitor->visit(this); }
}  // namespace daft::engine