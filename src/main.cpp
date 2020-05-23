#include <Minimal-Engine/Renderer.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Minimal-Engine/ShaderProgram.hpp>
#include <Minimal-Engine/Mesh.hpp>
#include <memory>

int width = 1600, height = 900;

void framebuffer_size_callback(GLFWwindow *window, int pwidth, int pheight);

std::unique_ptr<Renderer> renderer {nullptr};

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
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    renderer = std::make_unique<Renderer>(width, height);

    renderer->setShader(new ShaderProgram("shaders/color.vert.glsl", "shaders/color.frag.glsl"));

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
    renderer->addMesh(vertices, indices);

    while(!glfwWindowShouldClose(window)) {
        renderer->prepare();
        renderer->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Loader::clean();
    renderer.reset();
    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int pwidth, int pheight) {
    width = pwidth;
    height = pheight;
    renderer->resize(width, height);
}