//
// Created by mathis on 23/05/2020.
//
#include "Renderer.hpp"

#include <Core/Rendering/ShaderProgram.hpp>
#include <Core/Utils/Logger.hpp>
#include <Engine/Drawables/Object/primitives.hpp>
#include <Engine/Renderer/QuadRenderer.hpp>
#include <Engine/Renderer/RenderPasses/MultiSamplingPass.hpp>
#include <iostream>

namespace daft::engine {
Renderer::Renderer(int width, int height) {
    m_width = width;
    m_height = height;
    if (!GLinitialized) {
        if (!gladLoadGL()) {
            std::stringstream ss;
            ss << "Failed to load OpenGL.";
            daft::core::Logger::error(std::move(ss));
            exit(-1);
        }
        GLinitialized = true;
    }

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_MULTISAMPLE);
    glDepthFunc(GL_LESS);

    m_root = std::make_shared<Composite>();
    m_lightPool = std::make_unique<LightPool>();

    m_shaders.push_back(
        std::make_shared<core::ShaderProgram>("shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl"));
    m_shaders.push_back(std::make_shared<core::ShaderProgram>("shaders/color.vert.glsl", "shaders/color.frag.glsl"));
    m_multisamplePass = std::make_shared<daft::engine::MultiSamplingPass>(2048, 2048, 32);
    m_screenQuad = std::make_shared<daft::engine::QuadRenderer>();
    m_screenQuad->addQuad(-1.f, 1.f, 2.f, 2.f);
    m_screenQuad->quad(0).setTexture(m_multisamplePass->outTexture());

    updateProjectionMatrix();
    updateViewMatrix();
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    clearGL();

    m_root->update();

    _removeSelection();
    _addDrawable();
    _setSelection();
    _setShader();
}

void Renderer::clearGL() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(m_defaultSkyColor.x, m_defaultSkyColor.y, m_defaultSkyColor.z, 1.f);
}

void Renderer::render() {
    /// prepare opengl objects
    m_multisamplePass->use();
    clearGL();

    m_shaders[0]->use();
    /// add lights to shader
    m_lightPool->loadToShader(*m_shaders[0]);
    /// draw objects
    glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
    m_root->render(*m_shaders[0]);
    m_shaders[0]->stop();

    if (m_drawEdges) {
        m_shaders[1]->use();
        /// draw objects' edges
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        m_shaders[1]->setVec3("color", glm::vec3{0.f});
        m_root->renderEdges(*m_shaders[1]);
        m_shaders[1]->stop();
    }

    /// unbind opengl objects
    m_multisamplePass->stop(m_width, m_height);

    /// render the frame-textured quad to the screen.
    m_screenQuad->prepare();
    m_screenQuad->render();
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
    updateProjectionMatrix();
}

bool Renderer::GLinitialized{false};

void Renderer::processMouseScroll(float offset) {
    m_camera.processMouseScroll(offset);
    updateViewMatrix();
}

void Renderer::processMousePress(daft::engine::Camera::Mouse mouse) { m_camera.processMousePress(mouse); }

void Renderer::processMouseRelease() { m_camera.processMouseRelease(); }

void Renderer::processMouseMove(glm::vec2 mousePos) {
    m_camera.processMouseMove(mousePos);
    updateViewMatrix();
}

daft::engine::Drawable *Renderer::getSelection() {
    if (m_selection.empty()) return nullptr;
    return m_root->find(m_selection);
}

void Renderer::setSelection(std::string s) {
    auto selection = getSelection();
    if (selection) selection->unselect();
    m_selection = std::move(s);
}

void Renderer::updateViewMatrix() {
    for (const auto &shader : m_shaders) {
        shader->use();
        shader->setMat4("view", m_camera.getViewMatrix());
        shader->stop();
    }
}

void Renderer::updateProjectionMatrix() {
    for (const auto &shader : m_shaders) {
        shader->use();
        shader->setMat4("projection", glm::perspective(m_camera.fov(), float(m_width) / float(m_height), 0.1f, 500.f));
        shader->stop();
    }
}

void Renderer::switchToEditionMode() {
    m_drawEdges = true;
    m_defaultSkyColor = {0.35f, 0.35f, 0.35f};
}

void Renderer::switchToRenderingMode() {
    m_drawEdges = false;
    m_defaultSkyColor = {0.52f, 0.81f, 0.92f};
}

void Renderer::_removeSelection() {
    if (m_removeNextFrame) {
        auto selection = getSelection();
        if (selection && selection->isLight()) m_lightPool->remove(m_selection);
        m_root->remove(m_selection);
        m_removeNextFrame = false;
    }
}

void Renderer::_addDrawable() {
    std::shared_ptr<Drawable> drawable;
    switch (m_addNextFrame) {
        case Drawable::Type::None:
            return;
        case Drawable::Type::Group:
            drawable = std::make_shared<Composite>();
            break;
        case Drawable::Type::Sphere:
            drawable = std::make_shared<Sphere>();
            break;
        case Drawable::Type::Torus:
            drawable = std::make_shared<Torus>();
            break;
        case Drawable::Type::Cube:
            drawable = std::make_shared<Cube>();
            break;
        case Drawable::Type::BSpline: {
            std::vector<glm::vec3> controlPoints;
            controlPoints.emplace_back(glm::vec3{0.f});
            drawable = std::make_shared<BSpline>(controlPoints, 1);
            break;
        }
        case Drawable::Type::PointLight: {
            auto toAdd = std::make_shared<PointLight>();
            drawable = toAdd;
            m_lightPool->add(toAdd);
            break;
        }
        default:
            return;
    }
    m_addNextFrame = Drawable::Type::None;

    auto selection = getSelection();
    if (selection && selection->isComposite()) {
        dynamic_cast<daft::engine::Composite *>(selection)->add(drawable);
    } else {
        m_root->add(drawable);
    }
    setSelection(drawable->name());
}

void Renderer::_setSelection() {
    auto selection = getSelection();
    if (selection && !selection->selected()) {
        selection->select();
    }
}

void Renderer::_setShader() {
    switch (m_newShader) {
        case Renderer::AvailableShaders::BlinnPhong:
            m_shaders[0].reset();
            m_shaders[0] =
                std::make_shared<core::ShaderProgram>("shaders/blinnphong.vert.glsl", "shaders/blinnphong.frag.glsl");
            break;
        case Renderer::AvailableShaders::Phong:
            m_shaders[0].reset();
            m_shaders[0] = std::make_shared<core::ShaderProgram>("shaders/phong.vert.glsl", "shaders/phong.frag.glsl");
        default:
            break;
    }
    m_newShader = Renderer::AvailableShaders::None;
    updateViewMatrix();
    updateProjectionMatrix();
}
}  // namespace daft::engine