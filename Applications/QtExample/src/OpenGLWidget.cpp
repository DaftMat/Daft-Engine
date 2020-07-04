//
// Created by mathis on 04/07/2020.
//
#include "OpenGLWidget.hpp"

#include <Core/Utils/Log.hpp>
#include <QOpenGLContext>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL() {
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &OpenGLWidget::cleanup);

    resize(1600, 900);
    m_renderer = std::make_unique<Renderer>(width(), height());
    prepareScene();
}
void OpenGLWidget::paintGL() {
    m_renderer->prepare();
    m_renderer->render();
}

void OpenGLWidget::resizeGL(int width, int height) { m_renderer->resize(width, height); }

void OpenGLWidget::prepareScene() {
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

    m_renderer->addMesh(attribManager, indices);
    APP_INFO("Example scene loaded");
}
