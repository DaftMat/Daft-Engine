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
#include <Engine/Drawables/Object/Sphere.hpp>
#include <Engine/Renderer/Cameras/Camera.hpp>
#include <memory>
#include <vector>

#include "DeleterVisitor.hpp"

class ENGINE_API Renderer : public daft::core::NonCopyable {
   public:
    Renderer() = default;

    Renderer(int width, int height);

    ~Renderer() noexcept {
        m_deleter->visit(m_root.get());
        m_root.reset();
    }

    Renderer(Renderer &&other) noexcept
        : m_width{other.m_width}, m_height{other.m_height}, m_root{std::move_if_noexcept(other.m_root)} {}

    Renderer &operator=(Renderer &&other) noexcept;

    void prepare();

    void render();

    void resize(int width, int height);

    void addMesh(daft::core::AttribManager attribManager) noexcept {
        using namespace daft::engine;
        auto toAdd = new Object(nullptr, MeshObject(daft::core::Mesh(std::move_if_noexcept(attribManager))));
        m_root->add(toAdd);
        m_selection = toAdd->name();
    }

    void addSphere() {
        using namespace daft;
        auto toAdd = new engine::Sphere;
        m_root->add(toAdd);
        m_selection = toAdd->name();
    }

    daft::engine::Drawable *getSelection() {
        if (m_selection.empty()) return nullptr;
        return m_root->find(m_selection);
    }

    void setSelection(std::string s) { m_selection = std::move(s); }

    void processMouseScroll(float offset);

    void processMousePress(daft::engine::Camera::Mouse mouse);

    void processMouseRelease();

    void processMouseMove(glm::vec2 mousePos);

   private:
    static bool GLinitialized;
    int m_width{0}, m_height{0};
    std::string m_selection;

    std::shared_ptr<daft::engine::Composite> m_root{nullptr};

    std::unique_ptr<DeleterVisitor> m_deleter{nullptr};
    std::shared_ptr<daft::core::ShaderProgram> m_shader{nullptr};

    daft::engine::Camera m_camera;
};
