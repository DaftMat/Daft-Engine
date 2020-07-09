//
// Created by mathis on 08/07/2020.
//
#include "Light.hpp"

namespace daft::engine::objects {
void Light::render() {
    m_mesh.prepare();
    m_mesh.render(GL_LINES);
    m_mesh.unbind();
}
}  // namespace daft::engine::objects