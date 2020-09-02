//
// Created by mathis on 07/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <memory>

namespace daft {
/// forward declarations
namespace core {
class Material;
}  // namespace core

namespace engine {
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
    explicit MeshObject(Mesh mesh = Mesh{}, std::shared_ptr<Material> material = nullptr);

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
    Mesh &mesh() { return m_mesh; }

    /**
     * mesh constant reference getter.
     * @return const ref to mesh.
     */
    const Mesh &mesh() const { return m_mesh; }

   protected:
    Mesh m_mesh;
    std::shared_ptr<Material> m_material;
};
}  // namespace engine
}  // namespace daft