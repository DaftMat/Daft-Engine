//
// Created by mathis on 09/05/2020.
//

#include "Mesh.hpp"

Mesh::Mesh( std::vector<Vertex> vertices, std::vector<GLuint> indices ) noexcept {
    m_numVertex     = indices.size();
    int numVertices = vertices.size();
    glGenVertexArrays( 1, &m_vao );
    glGenBuffers( 1, &m_vbo );
    glGenBuffers( 1, &m_ebo );

    glBindVertexArray( m_vao );
    glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
    glBufferData( GL_ARRAY_BUFFER, numVertices * sizeof( Mesh::Vertex ), std::move( vertices ).data(), GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_ebo );
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, m_numVertex * sizeof( GLuint ), std::move( indices ).data(), GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Mesh::Vertex ), (void*)nullptr );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Mesh::Vertex ), (void*)offsetof( Mesh::Vertex, normal ) );
    glVertexAttribPointer(
        2, 2, GL_FLOAT, GL_FALSE, sizeof( Mesh::Vertex ), (void*)offsetof( Mesh::Vertex, texCoords ) );
    glBindVertexArray( 0 );
}

Mesh::~Mesh() noexcept {
    glDeleteBuffers( 1, &m_vbo );
    glDeleteBuffers( 1, &m_ebo );
    glDeleteVertexArrays( 1, &m_vao );
}

void Mesh::prepare() const noexcept {
    glBindVertexArray( m_vao );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
}

void Mesh::render( GLuint type ) const noexcept {
    glDrawElements( type, m_numVertex, GL_UNSIGNED_INT, nullptr );
}

void Mesh::unbind() const noexcept {
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    glBindVertexArray( 0 );
}
