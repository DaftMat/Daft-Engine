//
// Created by mathis on 23/05/2020.
//
#include "Loader.hpp"

Mesh Loader::loadMesh(const std::vector<Mesh::Vertex> &vertices, const std::vector<GLuint> &indices) {
    GLuint vao, vbo, ebo;
    glGenVertexArrays( 1, &vao );
    glGenBuffers( 1, &vbo );
    glGenBuffers( 1, &ebo );

    glBindVertexArray( vao );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER,
                  vertices.size() * sizeof( Mesh::Vertex ),
                  vertices.data(),
                  GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER,
                  indices.size() * sizeof( GLuint ),
                  indices.data(),
                  GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Mesh::Vertex ), (void*)nullptr );
    glVertexAttribPointer(
            1, 3, GL_FLOAT, GL_FALSE, sizeof( Mesh::Vertex ), (void*)offsetof( Mesh::Vertex, normal ) );
    glVertexAttribPointer( 2,
                           2,
                           GL_FLOAT,
                           GL_FALSE,
                           sizeof( Mesh::Vertex ),
                           (void*)offsetof( Mesh::Vertex, texCoords ) );

    glBindVertexArray( 0 );
    m_vaos.push_back(vao);
    m_vbos.push_back(vbo);
    m_vbos.push_back(ebo);
    return Mesh(vao, indices.size());
}

void Loader::clean() {
    for (auto &vao : m_vaos)
        glDeleteVertexArrays(1, &vao);
    for (auto &vbo : m_vbos)
        glDeleteBuffers(1, &vbo);
}

std::vector<GLuint> Loader::m_vaos {};
std::vector<GLuint> Loader::m_vbos {};