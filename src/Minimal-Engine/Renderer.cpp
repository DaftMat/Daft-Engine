//
// Created by mathis on 23/05/2020.
//
#include "Renderer.hpp"

#include <Core/Utils/Logger.hpp>
#include <iostream>

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

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_MULTISAMPLE);
    glDepthFunc(GL_LESS);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CW);

    m_root = std::make_shared<daft::engine::Composite>();
    m_shaders.push_back(
        std::make_shared<daft::core::ShaderProgram>("shaders/color.vert.glsl", "shaders/color.frag.glsl"));
    m_fbos.emplace_back(2048, 2048, 32, daft::core::FrameBufferObject::Attachments{});
    m_fbos.emplace_back(
        2048, 2048, 1,
        daft::core::FrameBufferObject::Attachments{daft::core::FrameBufferObject::Attachments::Type::TEXTURE, 1,
                                                   daft::core::FrameBufferObject::Attachments::Type::TEXTURE});
    // m_objRenderer = std::make_unique<daft::engine::ObjectRenderer>(m_fbos[0], m_shaders[0]);
    // m_lineRenderer = std::make_unique<daft::engine::LineRenderer>(m_fbos[0], m_shaders[0]);
    m_screenQuad = std::make_shared<daft::engine::QuadRenderer>();
    m_screenQuad->addQuad(-1.f, 1.f, 2.f, 2.f);
    m_screenQuad->quad(0).setTexture(m_fbos[1].textures()[0]);
    m_deleter = std::make_unique<DeleterVisitor>();

    updateProjectionMatrix();
    updateViewMatrix();
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    clearGL();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Renderer::clearGL() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.3f, 0.3f, 0.3f, 1.f);
}

void Renderer::render() {
    m_root->update();

    // m_objRenderer->prepare();
    m_shaders[0]->use();
    m_fbos[0].use();
    clearGL();
    m_shaders[0]->setVec3("color", {0.f, 0.f, 1.f});
    m_root->render(*m_shaders[0], GL_TRIANGLES);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_shaders[0]->setVec3("color", glm::vec3{0.f});
    m_root->render(*m_shaders[0], GL_TRIANGLES);
    // m_objRenderer->render(m_root.get());
    // m_objRenderer->unbind(m_width, m_height);

    // m_lineRenderer->prepare();
    // m_lineRenderer->render(m_root.get());
    // m_lineRenderer->unbind(m_width, m_height);
    m_fbos[0].stop(m_width, m_height);
    // glFinish();
    // glFlush();

    m_shaders[0]->stop();

    m_fbos[0].resolve(m_fbos[1]);

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
