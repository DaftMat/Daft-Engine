//
// Created by mathis on 08/07/2020.
//
#include "Object.hpp"

#include <Core/Materials/Material.hpp>
#include <Core/Utils/DrawableVisitor.hpp>

namespace daft::engine {

int Object::m_nrObject{0};

Object::Object(Composite *parent, std::string name) : Drawable(parent, std::move_if_noexcept(name)) {}

Object::~Object() noexcept { Object::reset(); }

void Object::render(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    for (auto &mo : m_meshObjects) {
        mo.prepare();
        if (mo.hasMaterial()) mo.material().loadToShader(shader);
        mo.render();
        mo.unbind();
    }
}

void Object::renderEdges(const core::ShaderProgram &shader) {
    shader.setMat4("model", model());
    if (selected()) shader.setVec3("color", {1.f, 1.f, 0.f});
    for (auto &mo : m_meshObjects) {
        mo.prepare();
        mo.render();
        mo.unbind();
    }
    if (selected()) shader.setVec3("color", glm::vec3{0.f});
}

void Object::accept(Drawable::DrawableVisitor *visitor) { visitor->visit(this); }

void Object::reset() {
    Drawable::reset();
    m_meshObjects.clear();
}

void Object::subdivide() {
    /// in the future : half-edges
}

}  // namespace daft::engine