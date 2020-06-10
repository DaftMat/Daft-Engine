//
// Created by mathis on 24/05/2020.
//
#include "GLFWExample.hpp"

#include <Core/Log.hpp>

#include "GLFWWindow.hpp"

GLFWExample::GLFWExample() {
    init(1600, 900);
    auto &renderer = *m_renderer;
    GLFWWindow::setFramebufferCallback([&renderer](int width, int height) { renderer.resize(width, height); });
    loadExampleScene();
    APP_INFO("Application created.");
}

void GLFWExample::loadExampleScene() {
    APP_INFO("Loading example scene...");
    m_renderer->setShader(new ShaderProgram("shaders/color.vert.glsl", "shaders/color.frag.glsl"));

    std::vector<Mesh::Vertex> vertices;
    std::vector<GLuint> indices{0, 2, 3, 0, 1, 2};
    Mesh::Vertex vertex{};
    vertex.texCoords = ProjName::Core::Utils::toGlm(ProjName::Core::Utils::Vector2f{0.f, 0.f});
    vertex.normal = {1.f, 1.f, 1.f};
    vertex.position = {-0.5f, -0.5f, 0.5f};
    vertices.push_back(vertex);
    vertex.texCoords = {1.f, 0.f};
    vertex.normal = ProjName::Core::Utils::toGlm(ProjName::Core::Utils::Vector3f{1.f, 0.f, 0.f});
    vertex.position = {0.5f, -0.5f, 0.f};
    vertices.push_back(vertex);
    vertex.texCoords = {1.f, 1.f};
    vertex.normal = {0.f, 1.f, 0.f};
    vertex.position = {0.5f, 0.5f, 0.f};
    vertices.push_back(vertex);
    vertex.texCoords = {0.f, 1.f};
    vertex.normal = {0.f, 0.f, 1.f};
    vertex.position = {-0.5f, 0.5f, 0.f};
    vertices.push_back(vertex);
    m_renderer->addMesh(vertices, indices);
    APP_INFO("Example scene loaded");
}

void GLFWExample::draw(double deltatime) {
    m_renderer->prepare();
    m_renderer->render();
}

void GLFWExample::run() {
    APP_INFO("launching application...");
    while (!m_window->shouldClose()) {
        draw(0.0);
        m_window->finish();
    }
    APP_INFO("application got out of main loop");
}
