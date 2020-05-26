//
// Created by mathis on 23/05/2020.
//
#include <iostream>
#include <Core/Log.hpp>
#include "Renderer.hpp"

Renderer::Renderer(int width, int height) : m_width{width}, m_height{height} {
    if (!gladLoadGL()) {
        ENGINE_ERROR("Failed to load OpenGL.");
        exit(-1);
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
