//
// Created by mathis on 24/05/2020.
//
#include <iostream>
#include "GLFWWindow.hpp"

void GLFWWindow::init(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width,height, "Engine Example Works !", nullptr, nullptr);
    if (m_window == nullptr) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback( m_window, framebuffer_size_callback );
}

void GLFWWindow::finish() {
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

GLFWwindow *GLFWWindow::m_window;
std::function<void(int,int)> GLFWWindow::m_framebufferCallback {[](int,int){}};