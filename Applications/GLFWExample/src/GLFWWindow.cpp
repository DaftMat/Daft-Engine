//
// Created by mathis on 24/05/2020.
//
#include <Core/Log.hpp>
#include "GLFWWindow.hpp"

GLFWWindow::GLFWWindow(int width, int height) {
    APP_INFO("Creating window...");
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width,height, "Engine Example Works !", nullptr, nullptr);
    if (m_window == nullptr) {
        APP_ERROR("Failed to create GLFW window.");
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback( m_window, framebuffer_size_callback );
    APP_INFO("Window created.");
}

void GLFWWindow::finish() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

std::function<void(int,int)> GLFWWindow::m_framebufferCallback {[](int,int){}};

void GLFWWindow::terminate() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
    APP_INFO("Window closed. Closing application...");
}
