//
// Created by mathis on 23/05/2020.
//
#include "Renderer.hpp"

#include <Core/Utils/Logger.hpp>
#include <iostream>

Renderer &Renderer::operator=(Renderer &&other) noexcept {
    m_width = other.m_width;
    m_height = other.m_height;
    m_root = std::move_if_noexcept(other.m_root);
    return *this;
}

Renderer::Renderer(int width, int height) : m_width{width}, m_height{height} {
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
    m_shader = std::make_shared<daft::core::ShaderProgram>("shaders/color.vert.glsl", "shaders/color.frag.glsl");
    m_deleter = std::make_unique<DeleterVisitor>();

    m_shader->use();
    m_shader->setMat4("projection", glm::perspective(m_camera.fov(), float(m_width) / float(m_height), 0.1f, 500.f));
    m_shader->setMat4("view", m_camera.getViewMatrix());
    m_shader->stop();

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
}

void Renderer::render() { m_root->render(*m_shader); }

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
    m_shader->use();
    m_shader->setMat4("projection", glm::perspective(m_camera.fov(), float(m_width) / float(m_height), 0.1f, 500.f));
    m_shader->stop();
}

bool Renderer::GLinitialized{false};

void Renderer::processMouseScroll(float offset) {
    m_camera.processMouseScroll(offset);
    m_shader->use();
    m_shader->setMat4("view", m_camera.getViewMatrix());
    m_shader->stop();
}

void Renderer::processMousePress(glm::vec2 mousePos) { m_camera.processMousePress(mousePos); }

void Renderer::processMouseRelease() { m_camera.processMouseRelease(); }

void Renderer::processMouseMove(glm::vec2 mousePos) {
    m_camera.processMouseMove(mousePos);
    m_shader->use();
    m_shader->setMat4("view", m_camera.getViewMatrix());
    m_shader->stop();
}
