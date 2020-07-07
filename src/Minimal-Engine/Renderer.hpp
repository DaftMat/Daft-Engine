//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Core/Geometry/ShaderProgram.hpp>
#include <memory>
#include <vector>

class ENGINE_API Renderer : public daft::core::utils::NonCopyable {
   public:
    Renderer() = default;

    Renderer(int width, int height);

    ~Renderer() = default;

    Renderer(Renderer &&other) noexcept
        : m_width{other.m_width},
          m_height{other.m_height},
          m_shader{std::move(other.m_shader)},
          m_meshes{std::move(other.m_meshes)} {}

    Renderer &operator=(Renderer &&other) noexcept;

    void prepare();

    void render();

    void resize(int width, int height);

    void addMesh(daft::core::geometry::AttribManager attribManager) noexcept {
        m_meshes.emplace_back(std::move_if_noexcept(attribManager));
    }

    void setShader(daft::core::geometry::ShaderProgram *shaderProgram) { m_shader.reset(shaderProgram); }

    [[nodiscard]] const daft::core::geometry::ShaderProgram &shader() const { return *m_shader; }

   private:
    static bool GLinitialized;
    int m_width{0}, m_height{0};

    std::unique_ptr<daft::core::geometry::ShaderProgram> m_shader{nullptr};
    std::vector<daft::core::geometry::Mesh> m_meshes;
};
