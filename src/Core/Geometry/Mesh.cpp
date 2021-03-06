//
// Created by mathis on 09/05/2020.
//

#include "Mesh.hpp"

#include <Core/Utils/Logger.hpp>

namespace daft::core {

Mesh::Mesh(Mesh&& o) noexcept
    : m_vao{o.m_vao},
      m_ebo{o.m_ebo},
      m_numVertex{o.m_numVertex},
      m_vbos{std::move_if_noexcept(o.m_vbos)},
      m_isVisible{o.m_isVisible},
      m_attribManager{std::move_if_noexcept(o.m_attribManager)} {
    o.m_isVisible = false;
}

Mesh& Mesh::operator=(Mesh&& o) noexcept {
    m_vao = o.m_vao;
    m_ebo = o.m_ebo;
    m_numVertex = o.m_numVertex;
    m_vbos = std::move_if_noexcept(o.m_vbos);
    m_isVisible = o.m_isVisible;
    m_attribManager = std::move_if_noexcept(o.m_attribManager);
    o.m_isVisible = false;
    return *this;
}

void Mesh::prepare() const {
    if (!m_isVisible) return;
    glBindVertexArray(m_vao);
    for (auto i = 0ul; i < m_attribManager.size(); ++i) glEnableVertexAttribArray(i);
}

void Mesh::render(GLuint type) const {
    if (!m_isVisible) return;
    glDrawElements(type, m_numVertex, GL_UNSIGNED_INT, nullptr);
}

void Mesh::unbind() const {
    if (!m_isVisible) return;
    for (auto i = 0ul; i < m_attribManager.size(); ++i) glDisableVertexAttribArray(i);
    glBindVertexArray(0);
}

void Mesh::reset(AttribManager attribManager) {
    clear();

    m_attribManager = std::move(attribManager);
    m_numVertex = m_attribManager.indices().size();
    m_vbos = std::vector<GLuint>(m_attribManager.size(), 0);
    m_isVisible = true;

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(m_attribManager.size(), m_vbos.data());
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    m_attribManager.setAttribs(m_vbos);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_numVertex * sizeof(GLuint), m_attribManager.indices().data(),
                 GL_STATIC_DRAW);

    glBindVertexArray(0);
    std::stringstream ss;
    ss << "Mesh created. VAO: " << m_vao << ".";
    core::Logger::info(std::move(ss));
}
void Mesh::clear() {
    if (!m_isVisible) return;
    m_isVisible = false;
    glDeleteBuffers(m_attribManager.size(), m_vbos.data());
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
    m_attribManager.clear();
    std::stringstream ss;
    ss << "Mesh of VAO: " << m_vao << " deleted.";
    core::Logger::info(std::move(ss));
}

}  // namespace daft::core