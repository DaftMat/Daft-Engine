//
// Created by mathis on 02/09/2020.
//
#include "PassRenderer.hpp"

namespace daft::core {
void PassRenderer::prepare() {
    /*m_fbo->use();*/
    m_shader->use();
}

void PassRenderer::render(engine::Drawable *d) { d->render(*m_shader, m_renderType); }

void PassRenderer::unbind() {
    m_shader->stop();
    /*m_fbo->stop();*/
}
}  // namespace daft::core