//
// Created by mathis on 24/05/2020.
//
#pragma once


#include <GLFW/glfw3.h>
#include <functional>

class GLFWWindow {
public:
    static void init(int width, int height);

    static bool shouldClose() { return glfwWindowShouldClose(m_window); }

    static void setFramebufferCallback(std::function<void(int,int)> framebufferCallback)
    { m_framebufferCallback = std::move(framebufferCallback); }

    static void finish();

private:
    static GLFWwindow *m_window;

    static std::function<void(int,int)> m_framebufferCallback;

    static void framebuffer_size_callback(GLFWwindow *window, int pwidth, int pheight) { m_framebufferCallback(pwidth, pheight); }
};