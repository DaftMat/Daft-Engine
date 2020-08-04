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

class ENGINE_API Renderer : public daft::core::NonCopyable {
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

    void addMesh(daft::core::AttribManager attribManager) noexcept {
        using namespace daft::engine;
        m_root->add(new Object(nullptr, MeshObject(daft::core::Mesh(std::move_if_noexcept(attribManager)))));
        m_selection++;
    }

    daft::engine::Drawable *getSelection() {
        if (m_selection < 0) return nullptr;
        return m_root->drawables()[m_selection].get();
    }

    void setSelection(int s) { m_selection = s; }

   private:
    static bool GLinitialized;
    int m_width{0}, m_height{0};
    int m_selection{-1};

    std::shared_ptr<daft::engine::Composite> m_root{nullptr};

    std::unique_ptr<RendererVisitor> m_visitor{nullptr};
    std::unique_ptr<DeleterVisitor> m_deleter{nullptr};
};
