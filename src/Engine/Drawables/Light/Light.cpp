//
// Created by mathis on 08/07/2020.
//
#include "Light.hpp"

#include <Core/Geometry/ShaderProgram.hpp>

namespace daft::engine::objects {
void Light::render(const Shader &shader) {
    /// pre-cond: the shader is being used
    shader.setMat4("model", model());
    m_mesh.prepare();
    m_mesh.render(GL_LINES);
    m_mesh.unbind();
}
}  // namespace daft::engine::objects