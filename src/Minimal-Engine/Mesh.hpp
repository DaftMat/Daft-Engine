//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_MESH_HPP
#define DAFT_GAMEENGINE_MESH_HPP
#include <API.hpp>
#include <Core/NonCopyable.hpp>
#include <Core/OpenGL.hpp>
#include <vector>

using ProjName::Core::NonCopyable;
/** mesh class.
 * a triangle based mesh that associates geometry and topology
 */
class ENGINE_API Mesh : public NonCopyable {
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
    Mesh() noexcept : m_vao{0}, m_vbo{0}, m_ebo{0}, m_numVertex{0} {}

    /**
     * standard constructor.
     * @param vertices - geometry of the mesh.
     * @param indices - topology of the mesh.
     */
    Mesh(std::vector<Mesh::Vertex> vertices, std::vector<GLuint> indices) noexcept;

    /**
     * destructor.
     * deletes OpenGL objects related to this mesh.
     */
    ~Mesh() noexcept;

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
    void prepare() const noexcept;

    /**
     * Renders the mesh on the currently bound frame buffer.
     * @param type - type of rendering (GL_TRIANGLES, GL_LINES, ...).
     */
    void render(GLuint type) const noexcept;

    /**
     * Unbind the mesh from OpenGL after it was rendered.
     */
    void unbind() const noexcept;

   private:
    GLuint m_vao, m_vbo, m_ebo, m_numVertex;
};

#endif  // DAFT_GAMEENGINE_MESH_HPP
