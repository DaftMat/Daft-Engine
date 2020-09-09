//
// Created by mathis on 09/07/2020.
//
#include "Composite.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {
int Composite::m_nrComposite{0};

Composite::Composite(Composite *parent, std::string name) noexcept : Drawable(parent, std::move_if_noexcept(name)) {}

void Composite::render(const core::ShaderProgram &shader) {
    for (auto &d : m_drawables) {
        d->render(shader);
    }
}

void Composite::renderEdges(const core::ShaderProgram &shader) {
    if (selected()) shader.setVec3("color", {1.f, 0.5f, 0.f});
    for (auto &d : m_drawables) {
        d->renderEdges(shader);
    }
    if (selected()) shader.setVec3("color", glm::vec3{0.f});
}

void Composite::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void Composite::add(Drawable *drawable) {
    drawable->setParent(this);
    drawable->updateNextFrame();
    m_drawables.emplace_back(drawable);
}

bool Composite::remove(const std::string &pname) {
    if (pname == name()) return true;
    for (const auto &d : m_drawables) {
        if (d->remove(pname)) {
            m_drawables.erase(std::find(m_drawables.begin(), m_drawables.end(), d));
            break;
        }
    }
    return false;
}

void Composite::reset() {
    Drawable::reset();
    m_drawables.clear();
}

Drawable *Composite::find(const std::string &pname) {
    if (pname == name()) return this;
    for (auto &d : m_drawables) {
        Drawable *found = d->find(pname);
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