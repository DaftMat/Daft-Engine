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
namespace core::mat {
class Material;
}  // namespace core::mat

namespace engine::objects {
/**
 * Wrapper for Mesh and a Material .
 */
class ENGINE_API MeshObject : public core::utils::NonCopyable {
   public:
    using Mesh = core::geometry::Mesh;
    using Material = core::mat::Material;

    /**
     * Standard / default constructor.
     * @param mesh - mesh wrapped.
     * @param material - material wrapped.
     */
    explicit MeshObject(Mesh mesh = Mesh{},
                        const std::shared_ptr<Material> &material = std::shared_ptr<Material>{nullptr});

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
    void prepare();

    /**
     * render the wrapped mesh with its material.
     * @param mode - rendering mode.
     */
    void render(GLuint mode = GL_TRIANGLES) const;

    /**
     * unbind the wrapped mesh and its material from the rendering context.
     */
    void unbind() const;

   private:
    Mesh m_mesh;
    std::weak_ptr<Material> m_material;
};
}  // namespace engine::objects
}  // namespace daft