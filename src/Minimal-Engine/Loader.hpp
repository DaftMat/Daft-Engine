//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>


#include "Mesh.hpp"

class ENGINE_API Loader {
public:
    static Mesh loadMesh(const std::vector<Mesh::Vertex> &vertices, const std::vector<GLuint> &indices);

    static void clean();
private:
    static std::vector<GLuint> m_vaos;
    static std::vector<GLuint> m_vbos;
};
