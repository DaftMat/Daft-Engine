//
// Created by mathis on 08/07/2020.
//
#include "Light.hpp"

namespace daft::engine {
int Light::m_nrLight{0};

void Light::renderEdges(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    if (selected())
        shader.setVec3("color", {1.f, 1.f, 0.f});
    else
        shader.setVec3("color", glm::vec3{1.f});
    m_mesh.prepare();
    m_mesh.render(GL_LINES);
    m_mesh.unbind();
    shader.setVec3("color", glm::vec3{0.f});
}

void Light::reset() {
    Drawable::reset();
    m_mesh.clear();
}
}  // namespace daft::engine