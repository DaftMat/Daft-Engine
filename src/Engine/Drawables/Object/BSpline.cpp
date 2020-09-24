//
// Created by daftmat on 23/09/2020.
//

#include "BSpline.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int BSpline::m_nrBSpline{0};

BSpline::BSpline(std::vector<glm::vec3> controlPoints, int base, float steps, Composite *parent, std::string name)
    : Object(parent, std::move(name)), m_spline{std::move(controlPoints), base}, m_steps{steps} {
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
    /// create modal vector
    m_spline.modalVector().clear();
    for (int i = 0; i < m_spline.base() + int(m_spline.controlPoints().size()) + 1; ++i)
        m_spline.modalVector().push_back(float(i));

    m_meshObjects.clear();
    /// from:   m_modalVector[m_base]
    /// to:     m_modalVector[m_modalVector.size()]
    core::AttribManager am{};
    std::vector<glm::vec3> positions;
    int index = 0;
    float umin = m_spline.modalVector()[m_spline.base()];
    float umax = m_spline.modalVector()[m_spline.controlPoints().size()];
    for (float u = umin; u < umax; u += (umax - umin) / m_steps) {
        if (index > 0) {
            am.indices().push_back(index - 1);
            am.indices().push_back(index++);
        } else
            index++;
        positions.push_back(m_spline.eval(u));
    }
    am.addAttrib(positions);
    m_meshObjects.emplace_back(core::Mesh{am});

    /// control polygon to display
    am.clear();
    am.addAttrib(m_spline.controlPoints());
    for (size_t i = 0; i < m_spline.controlPoints().size() - 1; ++i) {
        am.indices().push_back(i);
        am.indices().push_back(i + 1);
    }
    m_meshObjects.emplace_back(core::Mesh{am});
}

core::SettingManager BSpline::getSettings() const {
    core::SettingManager sm;
    sm.add("Base", m_spline.base());
    sm.add("Steps", m_steps);
    return sm;
}

void BSpline::setSettings(const core::SettingManager &s) {
    setBase(s.get<int>("Base"));
    setSteps(s.get<float>("Steps"));
}

void BSpline::setBase(int b) {
    if (m_spline.base() == b) return;
    m_spline.base() = b;
    updateNextFrame();
}

void BSpline::setSteps(float s) {
    if (m_steps == s) return;
    m_steps = s;
    updateNextFrame();
}

void BSpline::accept(core::DrawableVisitor *visitor) { visitor->visit(this); }
}  // namespace daft::engine