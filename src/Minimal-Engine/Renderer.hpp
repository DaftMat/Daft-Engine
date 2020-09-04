//
// Created by mathis on 23/05/2020.
//
#pragma once
#include <API.hpp>
#include <Core/Geometry/Mesh.hpp>
#include <Core/Rendering/ShaderProgram.hpp>
#include <Engine/Drawables/Composite.hpp>
#include <Engine/Drawables/MeshObject.hpp>
#include <Engine/Drawables/Object/Object.hpp>
#include <Engine/Drawables/Object/Sphere.hpp>
#include <Engine/Renderer/Cameras/Camera.hpp>
#include <Engine/Renderer/LineRenderer.hpp>
#include <Engine/Renderer/ObjectRenderer.hpp>
#include <Engine/Renderer/QuadRenderer.hpp>
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

    Renderer(Renderer &&other) noexcept : m_root{std::move_if_noexcept(other.m_root)} {}

    Renderer &operator=(Renderer &&other) noexcept;

    void prepare();

    void render();

    void resize(int width, int height);

    void addDrawable(daft::engine::Drawable *drawable) {
        auto selection = getSelection();
        if (selection && selection->isComposite()) {
            dynamic_cast<daft::engine::Composite *>(selection)->add(drawable);
        } else {
            m_root->add(drawable);
        }
        setSelection(drawable->name());
    }

    daft::engine::Drawable *getSelection() {
        if (m_selection.empty()) return nullptr;
        return m_root->find(m_selection);
    }

    daft::engine::Composite *getSceneTree() { return m_root.get(); }

    void setSelection(std::string s);

    void processMouseScroll(float offset);

    void processMousePress(daft::engine::Camera::Mouse mouse);

    void processMouseRelease();

    void processMouseMove(glm::vec2 mousePos);

    void updateViewMatrix();

    void updateProjectionMatrix();

   private:
    void clearGL() const;

    static bool GLinitialized;
    int m_width{0}, m_height{0};
    std::string m_selection;

    std::shared_ptr<daft::engine::Composite> m_root{nullptr};

    std::unique_ptr<DeleterVisitor> m_deleter{nullptr};
    std::unique_ptr<daft::engine::ObjectRenderer> m_objRenderer{nullptr};
    std::unique_ptr<daft::engine::LineRenderer> m_lineRenderer{nullptr};

    std::shared_ptr<daft::engine::QuadRenderer> m_screenQuad{nullptr};

    std::vector<std::shared_ptr<daft::core::ShaderProgram>> m_shaders;
    std::vector<daft::core::FrameBufferObject> m_fbos;

    daft::engine::Camera m_camera;
};
