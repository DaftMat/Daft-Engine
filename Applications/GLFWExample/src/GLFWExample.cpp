//
// Created by mathis on 24/05/2020.
//
#include "GLFWExample.hpp"

#include <Core/Utils/Log.hpp>

GLFWExample::GLFWExample() {
    init(1600, 900);
    auto &renderer = *m_renderer;
    GLFWWindow::setFramebufferCallback([&renderer](int width, int height) { renderer.resize(width, height); });
    loadExampleScene();
    APP_INFO("Application created.");
}

void GLFWExample::loadExampleScene() {
    APP_INFO("Loading example scene...");
    m_renderer->setShader(
        new stardust::core::geometry::ShaderProgram("shaders/color.vert.glsl", "shaders/color.frag.glsl"));

    stardust::core::geometry::AttribManager attribManager;
    std::vector<GLuint> indices{0, 2, 3, 0, 1, 2};
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> texCoords;

    texCoords.emplace_back(0.f, 0.f);
    normals.emplace_back(1.f, 1.f, 1.f);
    positions.emplace_back(-0.5f, -0.5f, 0.5f);

    texCoords.emplace_back(1.f, 0.f);
    normals.emplace_back(1.f, 0.f, 0.f);
    positions.emplace_back(0.5f, -0.5f, 0.f);

    texCoords.emplace_back(1.f, 1.f);
    normals.emplace_back(0.f, 1.f, 0.f);
    positions.emplace_back(0.5f, 0.5f, 0.f);

    texCoords.emplace_back(0.f, 1.f);
    normals.emplace_back(0.f, 0.f, 1.f);
    positions.emplace_back(-0.5f, 0.5f, 0.f);

    attribManager.addAttrib(positions);
    attribManager.addAttrib(normals);
    attribManager.addAttrib(texCoords);

    m_renderer->addMesh(std::move(attribManager), std::move(indices));
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
