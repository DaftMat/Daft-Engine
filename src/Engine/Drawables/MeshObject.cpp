//
// Created by mathis on 07/07/2020.
//
#include "MeshObject.hpp"

#include <Core/Materials/Material.hpp>
#include <utility>

namespace daft::engine {

MeshObject::MeshObject(Mesh mesh, std::shared_ptr<Material> material)
    : m_mesh{std::move(mesh)}, m_material{std::move(material)} {}

MeshObject::MeshObject(MeshObject &&o) noexcept
    : m_mesh{std::move_if_noexcept(o.m_mesh)}, m_material{std::move_if_noexcept(o.m_material)} {}

MeshObject &MeshObject::operator=(MeshObject &&o) noexcept {
    m_mesh = std::move_if_noexcept(o.m_mesh);
    m_material = std::move_if_noexcept(o.m_material);
    return *this;
}

void MeshObject::prepare() const {
    m_mesh.prepare();
    if (m_material == nullptr) return;  // m_material = std::make_shared</*Default*/ Material>();
    m_material->prepare();
}

void MeshObject::render(GLuint mode) const { m_mesh.render(mode); }

void MeshObject::unbind() const { m_mesh.unbind(); }

}  // namespace daft::engine