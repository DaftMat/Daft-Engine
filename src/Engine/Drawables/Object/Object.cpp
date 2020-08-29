//
// Created by mathis on 08/07/2020.
//
#include "Object.hpp"

#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {

int Object::m_nrObject{0};

Object::Object(Composite *parent, std::string name, std::vector<MeshObject> mos) noexcept
    : Drawable(parent, std::move_if_noexcept(name)), m_meshObjects{std::move_if_noexcept(mos)} {}

Object::Object(Composite *parent, MeshObject mo) noexcept : Drawable(parent), m_meshObjects{} {
    m_meshObjects.emplace_back(std::move_if_noexcept(mo));
}

Object::~Object() noexcept { Object::reset(); }

void Object::render(const core::ShaderProgram &shader) {
    shader.use();
    shader.setMat4("model", model());
    for (auto &mo : m_meshObjects) {
        mo.prepare();
        mo.render(GL_TRIANGLES);
        mo.unbind();
    }
    shader.stop();
}

void Object::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void Object::reset() {
    Drawable::reset();
    m_meshObjects.clear();
}

void Object::update() {
    if (m_update) {
        applyUpdate();
    }
}

}  // namespace daft::engine