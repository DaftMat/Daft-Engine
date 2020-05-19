#include <Core/OpenGL.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Minimal-Engine/ShaderProgram.hpp>
#include <Minimal-Engine/Mesh.hpp>

int width = 1600, height = 900;

void framebuffer_size_callback(GLFWwindow *window, int pwidth, int pheight);

int main() {
    /// window creation and setup.

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(width,height, "Hello world !", nullptr, nullptr);
    if (window == nullptr) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    /// initializing opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL." << std::endl;
        exit(-1);
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    ShaderProgram shader("shaders/color.vert.glsl", "shaders/color.frag.glsl");

    std::vector<Mesh::Vertex> vertices;
    std::vector<GLuint> indices{ 0, 2, 3, 0, 1, 2 };
    Mesh::Vertex vertex{};
    vertex.texCoords = { 0.f, 0.f };
    vertex.normal    = { 1.f, 1.f, 1.f };
    vertex.position  = { -0.5f, -0.5f, 0.5f };
    vertices.push_back( vertex );
    vertex.texCoords = { 1.f, 0.f };
    vertex.normal    = { 1.f, 0.f, 0.f };
    vertex.position  = { 0.5f, -0.5f, 0.f };
    vertices.push_back( vertex );
    vertex.texCoords = { 1.f, 1.f };
    vertex.normal    = { 0.f, 1.f, 0.f };
    vertex.position  = { 0.5f, 0.5f, 0.f };
    vertices.push_back( vertex );
    vertex.texCoords = { 0.f, 1.f };
    vertex.normal    = { 0.f, 0.f, 1.f };
    vertex.position  = { -0.5f, 0.5f, 0.f };
    vertices.push_back( vertex );
    Mesh mesh(vertices, indices);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        mesh.prepare();
        mesh.render(GL_TRIANGLES);
        mesh.unbind();
        shader.stop();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int pwidth, int pheight) {
    width = pwidth;
    height = pheight;
    glViewport(0, 0, width, height);
}