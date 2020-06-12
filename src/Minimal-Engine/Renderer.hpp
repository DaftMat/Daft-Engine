//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>
#include <memory>
#include <vector>

#include "Mesh.hpp"
#include "ShaderProgram.hpp"

class ENGINE_API Renderer : public ProjName::Core::NonCopyable {
   public:
    Renderer(int width, int height);

    ~Renderer() { m_shader.reset(); }

    Renderer(Renderer &&other) noexcept
        : m_width{other.m_width},
          m_height{other.m_height},
          m_shader{std::move(other.m_shader)},
          m_meshes{std::move(other.m_meshes)} {}

    Renderer &operator=(Renderer &&other) noexcept;

    void prepare();

    void render();

    void resize(int width, int height);

    void addMesh(std::vector<Mesh::Vertex> vertices, std::vector<GLuint> indices) noexcept {
        m_meshes.emplace_back(std::move_if_noexcept(vertices), std::move_if_noexcept(indices));
    }

    void setShader(ShaderProgram *shaderProgram) { m_shader.reset(shaderProgram); }

   private:
    static bool GLinitialized;
    int m_width, m_height;

    std::unique_ptr<ShaderProgram> m_shader{nullptr};
    std::vector<Mesh> m_meshes;
};
