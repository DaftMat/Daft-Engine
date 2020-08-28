//
// Created by mathis on 10/07/2020.
//
#include "RendererVisitor.hpp"

#include <Engine/Drawables/Object/primitives.hpp>

RendererVisitor::RendererVisitor()
    : m_shader{std::make_shared<daft::core::ShaderProgram>("shaders/color.vert.glsl", "shaders/color.frag.glsl")} {}

void RendererVisitor::visit(daft::engine::Composite *composite) { DrawableVisitor::visit(composite); }

template <typename T>
void RendererVisitor::render(T drawable) {
    m_shader->use();
    m_shader->setMat4("model", drawable->model());
    drawable->render();
    m_shader->stop();
}
