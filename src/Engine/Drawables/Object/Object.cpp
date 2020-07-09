//
// Created by mathis on 08/07/2020.
//
#include "Object.hpp"

#include <Core/Utils/DrawableVisitor.hpp>
#include <Engine/Drawables/MeshObject.hpp>

namespace daft::engine::objects {

Object::Object(Composite *parent, std::vector<MeshObject> mos) noexcept
    : Drawable(parent), m_meshObjects{std::move_if_noexcept(mos)} {}

Object::Object(Composite *parent, MeshObject mo) noexcept : Drawable(parent), m_meshObjects{} {
    m_meshObjects.emplace_back(std::move_if_noexcept(mo));
}

void Object::render() {
    for (auto &mo : m_meshObjects) {
        mo.prepare();
        mo.render(GL_TRIANGLES);
        mo.unbind();
    }
}

void Object::accept(const Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

}  // namespace daft::engine::objects