//
// Created by mathis on 07/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Core/Materials/Material.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <memory>

namespace daft::engine {
/**
 * Wrapper for Mesh and a Material .
 */
class ENGINE_API MeshObject : public core::NonCopyable {
   public:
    using Mesh = core::Mesh;
    using Material = core::Material;

    /**
     * Standard / default constructor.
     * @param mesh - mesh wrapped.
     * @param material - material wrapped.
     */
    explicit MeshObject(std::vector<Mesh> meshes = {},
                        std::shared_ptr<Material> material = std::make_shared<Material>());

    /**
     * Move constructor.
     * @param o - object to move.
     */
    MeshObject(MeshObject &&o) noexcept;

    /**
     * Move assignment operator.
     * @return ref to this.
     */
    MeshObject &operator=(MeshObject &&) noexcept;

    /**
     * prepares the wrapped mesh and its material to be rendered.
     */
    void prepare() const;

    /**
     * render the wrapped mesh with its material.
     * @param mode - rendering mode.
     */
    void render(GLuint mode = GL_TRIANGLES) const;

    /**
     * unbind the wrapped mesh and its material from the rendering context.
     */
    void unbind() const;

    /**
     * mesh reference getter.
     * @return ref to mesh.
     */
    std::vector<Mesh> &meshes() { return m_meshes; }

    /**
     * mesh constant reference getter.
     * @return const ref to mesh.
     */
    [[nodiscard]] const std::vector<Mesh> &meshes() const { return m_meshes; }

    /**
     * material reference getter.
     * @return ref to material.
     */
    Material &material() { return *m_material; }

    /**
     * material constant reference getter.
     * @return const ref to material.
     */
    [[nodiscard]] const Material &material() const { return *m_material; }

    /**
     * Checks if this MeshObject has a valid material.
     * @return true if its material isn't nullptr.
     */
    [[nodiscard]] bool hasMaterial() const { return m_material != nullptr; }

   protected:
    std::vector<Mesh> m_meshes;
    std::shared_ptr<Material> m_material;
};
}  // namespace daft::engine