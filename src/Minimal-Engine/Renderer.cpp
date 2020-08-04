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
    m_visitor = std::move_if_noexcept(other.m_visitor);
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
    m_visitor = std::make_unique<RendererVisitor>();
    m_deleter = std::make_unique<DeleterVisitor>();

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
}

void Renderer::render() { m_visitor->visit(m_root.get()); }

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
}

bool Renderer::GLinitialized{false};