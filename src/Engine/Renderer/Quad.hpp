//
// Created by mathis on 02/09/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Core/Materials/Material.hpp>
#include <memory>

namespace daft::engine {
/**
 * A MeshObject that is used as a screen.
 */
class ENGINE_API Quad {
   public:
    Quad(float x, float y, float width, float height);

    ~Quad() = default;

    Quad(Quad &&) noexcept = default;

    Quad &operator=(Quad &&) noexcept = default;

    void setTexture(int id);

    /**
     * prepares the wrapped mesh and its material to be rendered.
     */
    void prepare() const;

    /**
     * render the wrapped mesh with its material.
     * @param mode - rendering mode.
     */
    void render(const core::ShaderProgram &shader, GLuint mode = GL_TRIANGLES) const;

    void unbind() const { m_mesh.unbind(); }

   private:
    core::Mesh m_mesh;
    std::shared_ptr<core::Material> m_material;
};
}  // namespace daft::engine