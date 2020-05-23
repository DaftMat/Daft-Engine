//
// Created by mathis on 09/05/2020.
//

#include "Mesh.hpp"

void Mesh::prepare() const {
    glBindVertexArray( m_vao );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );
}

void Mesh::render( GLuint type ) const {
    glDrawElements( type, m_numVertex, GL_UNSIGNED_INT, nullptr );
}

void Mesh::unbind() const {
    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glDisableVertexAttribArray( 2 );
    glBindVertexArray( 0 );
}