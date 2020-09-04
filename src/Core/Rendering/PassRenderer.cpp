//
// Created by mathis on 02/09/2020.
//
#include "PassRenderer.hpp"

namespace daft::core {
void PassRenderer::prepare() {
    m_shader->use();
    if (m_fbo != nullptr) m_fbo->use();
}

void PassRenderer::render(engine::Drawable *d) { d->render(*m_shader, m_renderType); }

void PassRenderer::unbind(int width, int height) {
    if (m_fbo != nullptr) m_fbo->stop(width, height);
    m_shader->stop();
}
}  // namespace daft::core