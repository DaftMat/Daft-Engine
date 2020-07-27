//
// Created by mathis on 10/07/2020.
//
#include "RendererVisitor.hpp"

RendererVisitor::RendererVisitor()
    : m_shader{std::make_shared<daft::core::geometry::ShaderProgram>("shaders/color.vert.glsl",
                                                                     "shaders/color.frag.glsl")} {}

void RendererVisitor::visit(daft::engine::objects::Object *object) {
    m_shader->use();
    m_shader->setMat4("model", object->model());
    object->render();
    m_shader->stop();
}

void RendererVisitor::visit(daft::engine::objects::Composite *composite) { DrawableVisitor::visit(composite); }
