//
// Created by mathis on 04/07/2020.
//
#include "OpenGLWidget.hpp"

#include <QOpenGLContext>

namespace daft::app {
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL() {
    if (!m_glInitialized) {
        connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &OpenGLWidget::cleanup);

        m_renderer = std::make_unique<Renderer>(width(), height());
        prepareScene();
        m_glInitialized = true;
    }
}

void OpenGLWidget::paintGL() {
    m_renderer->prepare();
    m_renderer->render();
}

void OpenGLWidget::resizeGL(int width, int height) { m_renderer->resize(width, height); }

void OpenGLWidget::prepareScene() {
    std::stringstream ss;
    ss << "Loading example scene...";
    core::Logger::info(std::move(ss));

    daft::core::AttribManager attribManager;
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
    attribManager.setIndices(indices);

    // m_renderer->addMesh(attribManager);
    m_renderer->addSphere();

    std::stringstream ss2;
    ss2 << "Example scene loaded";
    core::Logger::info(std::move(ss2));
    emit selectionChanged();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e) {
    std::stringstream ss;
    ss << "Mouse pressed on OpenGL viewer at coordinates (" << e->pos().x() << "," << e->pos().y() << ")";
    core::Logger::debug(std::move(ss));

    if (e->button() == Qt::LeftButton) {
        m_renderer->processMousePress(glm::vec2{e->pos().x(), e->pos().y()});
    }
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e) {
    std::stringstream ss;
    ss << "Mouse released on OpenGL viewer at coordinates (" << e->pos().x() << "," << e->pos().y() << ").";
    core::Logger::debug(std::move(ss));

    if (e->button() == Qt::LeftButton) {
        m_renderer->processMouseRelease();
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *e) {
    std::stringstream ss;
    ss << "Mouse moved.";
    core::Logger::trace(std::move(ss));

    m_renderer->processMouseMove(glm::vec2{e->pos().x(), e->pos().y()});
    update();
    setFocus();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key::Key_S) {
        static int selection = -1;
        m_renderer->setSelection(selection);
        selection == 0 ? selection = -1 : selection = 0;
    }
    emit selectionChanged();
}

void OpenGLWidget::wheelEvent(QWheelEvent *e) {
    m_renderer->processMouseScroll(float(e->delta()) / 240.f);
    update();
    setFocus();
}
}  // namespace daft::app