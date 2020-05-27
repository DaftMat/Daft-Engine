//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>

#include <memory>
#include <vector>
#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Loader.hpp"

class ENGINE_API Renderer {
public:
    Renderer(int width, int height);
    ~Renderer() { m_shader.reset(); }

    void prepare();

    void render();

    void resize(int width, int height);

    void addMesh(const std::vector<Mesh::Vertex> &vertices, const std::vector<GLuint> &indices)
    { m_meshes.emplace_back(Loader::loadMesh(vertices, indices)); }

    void setShader(ShaderProgram *shaderProgram) {m_shader.reset(shaderProgram);}

private:
    int m_width, m_height;

    std::unique_ptr<ShaderProgram> m_shader{nullptr};
    std::vector<Mesh> m_meshes;
};
