//
// Created by mathis on 24/05/2020.
//
#pragma once
// clang-format off
#include <API.hpp>
#include <Engine/Renderer/Renderer.hpp>
#include <GLFW/glfw3.h>
#include <functional>
// clang-format on

namespace daft::app {
class ENGINE_API GLFWWindow {
   public:
    GLFWWindow(int width, int height);

    ~GLFWWindow() { terminate(); }

    bool shouldClose() { return glfwWindowShouldClose(m_window); }

    void draw() {
        m_renderer->prepare();
        m_renderer->render();
    }

    void finish();

    engine::Renderer& renderer() { return *m_renderer; }

    static void setFramebufferCallback(std::function<void(int, int)> framebufferCallback) {
        m_framebufferCallback = std::move(framebufferCallback);
    }

    static void setMouseMoveCallback(std::function<void(float, float)> mouseMoveCallback) {
        m_mouseMoveCallback = std::move(mouseMoveCallback);
    }

    static void setMousePressCallback(std::function<void(engine::Camera::Mouse)> mousePressCallback) {
        m_mousePressCallback = std::move(mousePressCallback);
    }

    static void setMouseReleaseCallback(std::function<void()> mouseReleaseCallback) {
        m_mouseReleaseCallback = std::move(mouseReleaseCallback);
    }

    static void setMouseScrollCallback(std::function<void(float)> mouseScrollCallback) {
        m_mouseScrollCallback = std::move(mouseScrollCallback);
    }

   private:
    void terminate();

    GLFWwindow* m_window;
    std::unique_ptr<engine::Renderer> m_renderer;

    static float m_mouseX, m_mouseY;

    static std::function<void(int, int)> m_framebufferCallback;
    static std::function<void(float, float)> m_mouseMoveCallback;
    static std::function<void(engine::Camera::Mouse)> m_mousePressCallback;
    static std::function<void()> m_mouseReleaseCallback;
    static std::function<void(float)> m_mouseScrollCallback;

    static void framebuffer_size_callback(GLFWwindow* window, int pwidth, int pheight) {
        m_framebufferCallback(pwidth, pheight);
    }
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
        m_mouseX = float(xpos);
        m_mouseY = float(ypos);
        m_mouseMoveCallback(xpos, ypos);
    }
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { m_mouseScrollCallback(yoffset); }
};
}  // namespace daft::app