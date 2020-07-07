//
// Created by mathis on 07/07/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Core/Materials/Material.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <memory>

namespace daft::engine::objects {
class ENGINE_API MeshObject : public core::utils::NonCopyable {
   public:
    using Mesh = core::geometry::Mesh;
    using Material = core::mat::Material;

    explicit MeshObject(Mesh mesh = Mesh{},
                        const std::shared_ptr<Material> &material = std::shared_ptr<Material>{nullptr});

    MeshObject(MeshObject &&o) noexcept;

    MeshObject &operator=(MeshObject &&) noexcept;

    void prepare();

    void render(GLuint mode = GL_TRIANGLES) const;

    void unbind() const;

   private:
    Mesh m_mesh;
    std::weak_ptr<Material> m_material;
};
}  // namespace daft::engine::objects