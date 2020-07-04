//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Core/Geometry/ShaderProgram.hpp>
#include <memory>
#include <vector>

class ENGINE_API Renderer : public stardust::core::utils::NonCopyable {
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

    void addMesh(stardust::core::geometry::AttribManager attribManager, std::vector<GLuint> indices) noexcept {
        m_meshes.emplace_back(std::move_if_noexcept(attribManager), std::move_if_noexcept(indices));
    }

    void setShader(stardust::core::geometry::ShaderProgram *shaderProgram) { m_shader.reset(shaderProgram); }

    [[nodiscard]] const stardust::core::geometry::ShaderProgram &shader() const { return *m_shader; }

   private:
    static bool GLinitialized;
    int m_width, m_height;

    std::unique_ptr<stardust::core::geometry::ShaderProgram> m_shader{nullptr};
    std::vector<stardust::core::geometry::Mesh> m_meshes;
};
