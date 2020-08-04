//
// Created by mathis on 08/07/2020.
//
#include "Light.hpp"

namespace daft::engine {
void Light::render() {
    m_mesh.prepare();
    m_mesh.render(GL_LINES);
    m_mesh.unbind();
}

void Light::reset() {
    Drawable::reset();
    m_mesh.clear();
}
}  // namespace daft::engine