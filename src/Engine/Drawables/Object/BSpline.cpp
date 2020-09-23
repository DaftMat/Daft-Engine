//
// Created by daftmat on 23/09/2020.
//

#include "BSpline.hpp"

namespace daft::engine {
int BSpline::m_nrBSpline{0};

void BSpline::createBSpline() {
    core::AttribManager am{};
    am.addAttrib(m_controlPoints);
    for (size_t i = 0; i < m_controlPoints.size() - 1; ++i) {
        am.indices().push_back(i);
        am.indices().push_back(i + 1);
    }
    m_meshObjects.clear();
    m_meshObjects.emplace_back(core::Mesh{am});
}

void BSpline::renderEdges(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    if (selected()) shader.setVec3("color", {1.f, 1.f, 0.f});
    for (auto &mo : m_meshObjects) {
        mo.prepare();
        mo.render(GL_LINES);
        mo.unbind();
    }
    if (selected()) shader.setVec3("color", glm::vec3{0.f});
}
}  // namespace daft::engine