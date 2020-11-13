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
    /**
     * Standard constructor.
     * @param x - x origin position.
     * @param y - y origin position.
     * @param width - width of the quad.
     * @param height - height of the quad.
     */
    Quad(float x, float y, float width, float height);

    /**
     * Default destructor.
     */
    ~Quad() = default;

    /**
     * Default move constructor.
     */
    Quad(Quad &&) noexcept = default;

    /**
     * Default move assignment operator.
     * @return ref to this.
     */
    Quad &operator=(Quad &&) noexcept = default;

    /**
     * Adds a texture to the quad.
     */
    void addTexture();

    /**
     * Sets the texture i of the quad.
     * @param id - texture.
     * @param i - index.
     */
    void setTexture(int id, int i = 0);

    /**
     * prepares the wrapped mesh and its material to be rendered.
     */
    void prepare() const;

    /**
     * render the wrapped mesh with its material.
     * @param mode - rendering mode.
     */
    void render(const core::ShaderProgram &shader, GLuint mode = GL_TRIANGLES) const;

    /**
     * Unbinds the quad from opengl context.
     */
    void unbind() const { m_mesh.unbind(); }

   private:
    core::Mesh m_mesh;
    std::shared_ptr<core::Material> m_material;
};
}  // namespace daft::engine