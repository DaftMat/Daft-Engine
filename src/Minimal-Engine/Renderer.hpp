//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Core/Geometry/ShaderProgram.hpp>
#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/MeshObject.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <memory>
#include <vector>

#include "DeleterVisitor.hpp"
#include "RendererVisitor.hpp"

class ENGINE_API Renderer : public daft::core::utils::NonCopyable {
   public:
    Renderer() = default;

    Renderer(int width, int height);

    ~Renderer() noexcept {
        m_deleter->visit(m_root.get());
        m_root.reset();
        m_visitor.reset();
    }

    Renderer(Renderer &&other) noexcept
        : m_width{other.m_width},
          m_height{other.m_height},
          m_root{std::move_if_noexcept(other.m_root)},
          m_visitor{std::move_if_noexcept(other.m_visitor)} {}

    Renderer &operator=(Renderer &&other) noexcept;

    void prepare();

    void render();

    void resize(int width, int height);

    void addMesh(daft::core::geometry::AttribManager attribManager) noexcept {
        using namespace daft::engine::objects;
        m_root->add(new Object(nullptr, MeshObject(daft::core::geometry::Mesh(std::move_if_noexcept(attribManager)))));
    }

   private:
    static bool GLinitialized;
    int m_width{0}, m_height{0};

    std::shared_ptr<daft::engine::objects::Composite> m_root{nullptr};

    std::unique_ptr<RendererVisitor> m_visitor{nullptr};
    std::unique_ptr<DeleterVisitor> m_deleter{nullptr};
};
