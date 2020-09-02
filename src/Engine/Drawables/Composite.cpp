//
// Created by mathis on 09/07/2020.
//
#include "Composite.hpp"

#include <Core/Geometry/ShaderProgram.hpp>
#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int Composite::m_nrComposite{0};

Composite::Composite(Composite *parent, std::string name) noexcept : Drawable(parent, std::move_if_noexcept(name)) {}

void Composite::render(const core::ShaderProgram &shader) {
    for (auto &d : m_drawables) {
        d->render(shader);
    }
}

void Composite::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void Composite::add(Drawable *drawable) {
    drawable->setParent(this);
    m_drawables.emplace_back(drawable);
}

void Composite::reset() {
    Drawable::reset();
    m_drawables.clear();
}

Drawable *Composite::find(const std::string &pname) {
    if (pname == name()) return this;
    Drawable *found;
    for (auto &d : m_drawables) {
        found = d->find(pname);
        if (found) return found;
    }
    return nullptr;
}

void Composite::update() {
    for (auto &d : m_drawables) {
        d->update();
    }
}

}  // namespace daft::engine