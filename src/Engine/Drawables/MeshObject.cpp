//
// Created by mathis on 07/07/2020.
//
#include "MeshObject.hpp"

#include <Core/Materials/Material.hpp>
#include <utility>

namespace daft::engine {

MeshObject::MeshObject(std::vector<Mesh> meshes, std::shared_ptr<Material> material)
    : m_meshes{std::move(meshes)}, m_material{std::move(material)} {}

MeshObject::MeshObject(MeshObject &&o) noexcept
    : m_meshes{std::move_if_noexcept(o.m_meshes)}, m_material{std::move_if_noexcept(o.m_material)} {}

MeshObject &MeshObject::operator=(MeshObject &&o) noexcept {
    m_meshes = std::move_if_noexcept(o.m_meshes);
    m_material = std::move_if_noexcept(o.m_material);
    return *this;
}

void MeshObject::prepare() const {
    if (m_material == nullptr) return;
    m_material->prepare();
}

void MeshObject::render(GLuint mode) const {
    for (const auto &mesh : m_meshes) {
        mesh.prepare();
        mesh.render(mode);
        mesh.unbind();
    }
}

void MeshObject::unbind() const {}

}  // namespace daft::engine