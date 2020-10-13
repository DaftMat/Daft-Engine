//
// Created by mathis on 24/05/2020.
//
#include "GLFWWindow.hpp"

namespace daft::app {

std::function<void(int, int)> GLFWWindow::m_framebufferCallback{[](int, int) {}};
std::function<void(float, float)> GLFWWindow::m_mouseMoveCallback{[](float, float) {}};
std::function<void(engine::Camera::Mouse)> GLFWWindow::m_mousePressCallback{[](engine::Camera::Mouse) {}};
std::function<void()> GLFWWindow::m_mouseReleaseCallback{[]() {}};
std::function<void(float)> GLFWWindow::m_mouseScrollCallback{[](float) {}};
float GLFWWindow::m_mouseX{0};
float GLFWWindow::m_mouseY{0};

GLFWWindow::GLFWWindow(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GL_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GL_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, "Hello Daft !", nullptr, nullptr);
    if (m_window == nullptr) {
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetScrollCallback(m_window, scroll_callback);
    m_renderer = std::make_unique<engine::Renderer>(width, height);
}

void GLFWWindow::finish() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void GLFWWindow::terminate() {
    m_renderer.reset();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void GLFWWindow::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    switch (action) {
        case GLFW_PRESS: {
            engine::Camera::Mouse mouse{};
            switch (button) {
                case GLFW_MOUSE_BUTTON_RIGHT:
                    mouse.button = engine::Camera::Mouse::Button::Right;
                    break;
                case GLFW_MOUSE_BUTTON_LEFT:
                    mouse.button = engine::Camera::Mouse::Button::Left;
                    break;
                case GLFW_MOUSE_BUTTON_MIDDLE:
                    mouse.button = engine::Camera::Mouse::Button::Wheel;
                    break;
                default:
                    return;
            }
            mouse.pos = {m_mouseX, m_mouseY};
            m_mousePressCallback(mouse);
            break;
        }
        case GLFW_RELEASE:
            m_mouseReleaseCallback();
            break;
        default:
            break;
    }
}
}  // namespace daft::app