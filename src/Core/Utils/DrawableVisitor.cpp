//
// Created by mathis on 09/07/2020.
//
#include "DrawableVisitor.hpp"

#include <Engine/Drawables/Composite.hpp>

namespace daft::core {
void DrawableVisitor::visit(engine::Composite *composite) {
    for (auto &d : composite->drawables()) {
        d->accept(this);
    }
}
}  // namespace daft::core