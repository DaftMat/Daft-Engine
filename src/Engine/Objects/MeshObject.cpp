//
// Created by mathis on 07/07/2020.
//
#include "MeshObject.hpp"

namespace daft::engine::objects {

MeshObject::MeshObject(Mesh mesh, const std::shared_ptr<Material> &material)
    : m_mesh{std::move(mesh)}, m_material{material} {}

MeshObject::MeshObject(MeshObject &&o) noexcept
    : m_mesh{std::move_if_noexcept(o.m_mesh)}, m_material{std::move_if_noexcept(o.m_material)} {}

MeshObject &MeshObject::operator=(MeshObject &&o) noexcept {
    m_mesh = std::move_if_noexcept(o.m_mesh);
    m_material = std::move_if_noexcept(o.m_material);
    return *this;
}

void MeshObject::prepare() {
    m_mesh.prepare();
    if (m_material.expired()) m_material = std::make_shared</*Default*/ Material>();
    m_material.lock()->prepare();
}

void MeshObject::render(GLuint mode) const { m_mesh.render(mode); }

void MeshObject::unbind() const { m_mesh.unbind(); }

}  // namespace daft::engine::objects