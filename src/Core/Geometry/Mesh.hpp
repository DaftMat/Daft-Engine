//
// Created by mathis on 09/05/2020.
//
#pragma once

#include <API.hpp>
#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <vector>

namespace stardust::core::geometry {
/** mesh class.
 * a triangle based mesh that associates geometry and topology
 */
class ENGINE_API Mesh : public utils::NonCopyable {
   public:
    /**
     * Intern structure of a vertex.
     */
    struct Vertex {
        glm::vec3 position;   ///< World position of the vertex.
        glm::vec3 normal;     ///< Normal of the surface on the vertex.
        glm::vec2 texCoords;  ///< Texture coordinates on the vertex.
    };

    /**
     * Default constructor.
     * Creates an non-existing mesh.
     */
    constexpr Mesh() noexcept : m_vao{0}, m_vbo{0}, m_ebo{0}, m_numVertex{0} {}

    /**
     * standard constructor.
     * @param vertices - geometry of the mesh.
     * @param indices - topology of the mesh.
     */
    Mesh(std::vector<Mesh::Vertex> vertices, std::vector<GLuint> indices);

    /**
     * destructor.
     * deletes OpenGL objects related to this mesh.
     */
    ~Mesh();

    /**
     * Move constructor.
     * @param other - mesh to move into this mesh.
     */
    Mesh(Mesh &&other) noexcept = default;

    /**
     * Move assignment operator.
     * @param other - mesh to move into this mesh.
     * @return this mesh after it was assigned to the other.
     */
    Mesh &operator=(Mesh &&other) noexcept = default;

    /**
     * Prepares the mesh to be rendered.
     */
    void prepare() const;

    /**
     * Renders the mesh on the currently bound frame buffer.
     * @param type - type of rendering (GL_TRIANGLES, GL_LINES, ...).
     */
    void render(GLuint type) const;

    /**
     * Unbind the mesh from OpenGL after it was rendered.
     */
    void unbind() const;

   private:
    GLuint m_vao, m_vbo, m_ebo, m_numVertex;
};
}  // namespace stardust::core::geometry