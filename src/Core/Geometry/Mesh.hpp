//
// Created by mathis on 09/05/2020.
//
#pragma once

#include <API.hpp>
#include <Core/OpenGL.hpp>
#include <Core/Utils/NonCopyable.hpp>
#include <vector>

#include "AttribManager.hpp"

namespace daft::core {
/**
 * mesh class.
 * a triangle based mesh that associates geometry and topology
 */
class ENGINE_API Mesh : public NonCopyable {
   public:
    /**
     * Default constructor.
     * Creates an non-existing mesh.
     */
    Mesh() noexcept : m_vao{0}, m_ebo{0}, m_numVertex{0}, m_isVisible{false} {}

    /**
     * standard constructor.
     * @param attribManager - geometry of the mesh.
     * @param indices - topology of the mesh.
     */
    explicit Mesh(const AttribManager &attribManager) { reset(attribManager); };

    /**
     * destructor.
     * deletes OpenGL objects related to this mesh.
     */
    ~Mesh() { clear(); }

    /**
     * Move constructor.
     * @param o - mesh to move into this mesh.
     */
    Mesh(Mesh &&o) noexcept;

    /**
     * Move assignment operator.
     * @param o - mesh to move into this mesh.
     * @return reference to this.
     */
    Mesh &operator=(Mesh &&o) noexcept;

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

    /**
     * Resets the geometry of the mesh
     * @param attribManager - geometry
     * @param indices - topology
     */
    void reset(const AttribManager &attribManager);

    /**
     * Clears the mesh.
     * deletes all opengl objects.
     */
    void clear();

    /**
     * AttribManager const ref getter.
     * @return const reference to the AttribManager.
     */
    const AttribManager &attribManager() const { return m_attribManager; }

    /**
     * AttribManager ref getter.
     * @return reference to the AttribManager.
     */
    AttribManager &attribManager() { return m_attribManager; }

   private:
    GLuint m_vao, m_ebo, m_numVertex;
    std::vector<GLuint> m_vbos;
    bool m_isVisible{false};
    AttribManager m_attribManager;
};
}  // namespace daft::core