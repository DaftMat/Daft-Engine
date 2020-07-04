//
// Created by mathis on 24/05/2020.
//
#pragma once

#include <GLFW/glfw3.h>

#include <API.hpp>
#include <Minimal-Engine/Renderer.hpp>
#include <functional>

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

    Renderer &renderer() { return *m_renderer; }

    static void setFramebufferCallback(std::function<void(int, int)> framebufferCallback) {
        m_framebufferCallback = std::move(framebufferCallback);
    }

   private:
    void terminate();

    GLFWwindow *m_window;
    std::unique_ptr<Renderer> m_renderer;

    static std::function<void(int, int)> m_framebufferCallback;

    static void framebuffer_size_callback(GLFWwindow *window, int pwidth, int pheight) {
        m_framebufferCallback(pwidth, pheight);
    }
};