//
// Created by mathis on 23/05/2020.
//
#include "Renderer.hpp"

#include <Core/Utils/Logger.hpp>
#include <iostream>

int Renderer::m_width{0};
int Renderer::m_height{0};

Renderer &Renderer::operator=(Renderer &&other) noexcept {
    m_root = std::move_if_noexcept(other.m_root);
    return *this;
}

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

    m_root = std::make_shared<daft::engine::Composite>();
    m_shaders.push_back(
        std::make_shared<daft::core::ShaderProgram>("shaders/color.vert.glsl", "shaders/color.frag.glsl"));
    m_fbos.push_back(std::make_shared<daft::core::FrameBufferObject>(
        1920, 1080, 32,
        daft::core::FrameBufferObject::Attachments{daft::core::FrameBufferObject::Attachments::Type::BUFFER}));
    m_fbos.push_back(std::make_shared<daft::core::FrameBufferObject>(
        1920, 1080, 1,
        daft::core::FrameBufferObject::Attachments{daft::core::FrameBufferObject::Attachments::Type::TEXTURE}));
    m_objRenderer = std::make_unique<daft::engine::ObjectRenderer>(nullptr, m_shaders[0]);
    m_lineRenderer = std::make_unique<daft::engine::LineRenderer>(nullptr, m_shaders[0]);
    m_screenQuad = std::make_shared<daft::engine::QuadRenderer>();
    m_screenQuad->addQuad(-1.f, 1.f, 2.f, 2.f);
    m_screenQuad->quad(0).setTexture(m_fbos[1]->textures()[0]);
    m_deleter = std::make_unique<DeleterVisitor>();

    updateProjectionMatrix();
    updateViewMatrix();

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::render() {
    m_root->update();

    m_objRenderer->prepare();
    m_objRenderer->render(m_root.get());
    m_objRenderer->unbind();

    m_lineRenderer->prepare();
    m_lineRenderer->render(m_root.get());
    m_lineRenderer->unbind();

    m_fbos[0]->resolve(*m_fbos[1]);

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

void Renderer::setSelection(std::string s) {
    auto selection = getSelection();
    if (selection) selection->unselect();
    m_selection = std::move(s);
    if (!m_selection.empty()) getSelection()->select();
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
