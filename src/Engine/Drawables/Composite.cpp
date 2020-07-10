//
// Created by mathis on 09/07/2020.
//
#include "Composite.hpp"

#include <Core/Geometry/ShaderProgram.hpp>
#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine::objects {
int Composite::m_nrComposite{0};

Composite::Composite(Composite *parent, std::string name) noexcept : Drawable(parent, std::move_if_noexcept(name)) {}

void Composite::render(const Shader &shader) {
    shader.use();
    for (auto &d : m_drawables) {
        d->render(shader);
    }
    shader.stop();
}

void Composite::accept(const Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void Composite::add(Drawable *drawable) {
    drawable->setParent(this);
    m_drawables.emplace_back(drawable);
}
}  // namespace daft::engine::objects