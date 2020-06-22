//
// Created by mathis on 23/05/2020.
//
#include "Renderer.hpp"

#include <Core/Utils/Log.hpp>
#include <iostream>

Renderer &Renderer::operator=(Renderer &&other) noexcept {
    m_width = other.m_width;
    m_height = other.m_height;
    m_shader = std::move(other.m_shader);
    m_meshes = std::move(other.m_meshes);
    return *this;
}

Renderer::Renderer(int width, int height) : m_width{width}, m_height{height} {
    if (!GLinitialized) {
        if (!gladLoadGL()) {
            ENGINE_ERROR("Failed to load OpenGL.");
            exit(-1);
        }
        GLinitialized = true;
    }

    glViewport(0, 0, m_width, m_height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void Renderer::prepare() {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);
}

void Renderer::render() {
    m_shader->use();
    for (const auto &mesh : m_meshes) {
        mesh.prepare();
        mesh.render(GL_TRIANGLES);
        mesh.unbind();
    }
    m_shader->stop();
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
}

bool Renderer::GLinitialized{false};