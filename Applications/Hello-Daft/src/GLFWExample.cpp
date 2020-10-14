//
// Created by mathis on 24/05/2020.
//
#include "GLFWExample.hpp"

namespace daft::app {
GLFWExample::GLFWExample() {
    init(1600, 900);
    auto &renderer = m_window->renderer();

    GLFWWindow::setFramebufferCallback([&renderer](int width, int height) { renderer.resize(width, height); });
    GLFWWindow::setMouseMoveCallback([&renderer](float xpos, float ypos) {
        renderer.processMouseMove(glm::vec2{xpos, ypos});
    });
    GLFWWindow::setMousePressCallback([&renderer](engine::Camera::Mouse mouse) { renderer.processMousePress(mouse); });
    GLFWWindow::setMouseReleaseCallback([&renderer]() { renderer.processMouseRelease(); });
    GLFWWindow::setMouseScrollCallback([&renderer](float offset) { renderer.processMouseScroll(offset); });

    loadExampleScene();
}

void GLFWExample::loadExampleScene() {
    m_window->renderer().addDrawable(engine::Drawable::Type::Cube);
    m_window->renderer().addDrawable(engine::Drawable::Type::DirLight);
    m_window->renderer().switchToRenderingMode();
}

void GLFWExample::draw(double deltatime) { m_window->draw(); }

void GLFWExample::run() {
    while (!m_window->shouldClose()) {
        draw(0.0);
        m_window->finish();
    }
}
}  // namespace daft::app