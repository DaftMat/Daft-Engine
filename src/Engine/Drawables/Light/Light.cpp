//
// Created by mathis on 08/07/2020.
//
#include "Light.hpp"

namespace daft::engine {
int Light::m_nrLight{0};

void Light::render(const core::ShaderProgram &shader) {
    shader.use();
    shader.setMat4("model", model());
    m_mesh.prepare();
    m_mesh.render(GL_LINES);
    m_mesh.unbind();
    shader.stop();
}

void Light::reset() {
    Drawable::reset();
    m_mesh.clear();
}
}  // namespace daft::engine