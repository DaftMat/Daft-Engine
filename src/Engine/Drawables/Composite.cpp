//
// Created by mathis on 09/07/2020.
//
#include "Composite.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine::objects {
void Composite::render() {
    for (auto &d : m_drawables) {
        d->render();
    }
}

void Composite::accept(const Drawable::DrawableVisitor *visitor) { visitor->visit(this); }
}  // namespace daft::engine::objects