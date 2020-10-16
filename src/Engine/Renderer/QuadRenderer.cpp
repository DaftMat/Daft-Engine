//
// Created by mathis on 02/09/2020.
//
#include "QuadRenderer.hpp"

namespace daft::engine {
QuadRenderer::QuadRenderer()
    : m_shader{std::make_shared<core::ShaderProgram>("shaders/quad.vert.glsl", "shaders/quad.frag.glsl")} {}

void QuadRenderer::prepare() const {
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void QuadRenderer::render() const {
    m_shader->use();
    for (const auto &quad : m_quads) {
        quad.prepare();
        quad.render(*m_shader, GL_TRIANGLES);
        quad.unbind();
    }
    m_shader->stop();
}
}  // namespace daft::engine