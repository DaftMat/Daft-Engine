//
// Created by mathis on 09/05/2020.
//

#ifndef DAFT_GAMEENGINE_MESH_HPP
#define DAFT_GAMEENGINE_MESH_HPP

#include <Core/OpenGL.hpp>
#include <vector>

/** mesh class.
 * a triangle based mesh that associates geometry and topology
 */
class Mesh
{
  public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh(Mesh&&) = delete;
    Mesh &operator=(const Mesh&) = delete;
    Mesh &operator=(Mesh&&) = delete;

    void prepare() const;

    void render( GLuint type ) const;

    void unbind() const;

  private:
    GLuint m_vao, m_vbo, m_ebo, m_numVertex;
};

#endif // DAFT_GAMEENGINE_MESH_HPP
