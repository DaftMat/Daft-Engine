//
// Created by mathis on 04/07/2020.
//
#include "OpenGLWidget.hpp"

#include <Engine/Drawables/Object/Sphere.hpp>
#include <QOpenGLContext>

namespace daft::app {
OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void OpenGLWidget::initializeGL() {
    if (!m_glInitialized) {
        connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &OpenGLWidget::cleanup);

        m_renderer = std::make_unique<engine::Renderer>(width(), height());
        prepareScene();
        m_glInitialized = true;

        emit glInitialized();
    }
}

void OpenGLWidget::paintGL() {
    /// find default fbo and bind it to the engine.
    core::BaseFrameBuffer::setDefaultFbo(defaultFramebufferObject());
    m_renderer->prepare();
    m_renderer->render();
    emitSelectionChanged();
    emitSceneTreeChanged();
}

void OpenGLWidget::resizeGL(int width, int height) { m_renderer->resize(width, height); }

void OpenGLWidget::prepareScene() {
    std::stringstream ss;
    ss << "Loading example scene...";
    core::Logger::info(std::move(ss));

    std::stringstream ss2;
    ss2 << "Example scene loaded";
    core::Logger::info(std::move(ss2));
    emit selectionChanged();
}

void OpenGLWidget::mousePressEvent(QMouseEvent *e) {
    std::stringstream ss;
    ss << "Mouse pressed on OpenGL viewer at coordinates (" << e->pos().x() << "," << e->pos().y() << ")";
    core::Logger::debug(std::move(ss));

    engine::Camera::Mouse mouse{};
    mouse.pos = glm::vec2{e->pos().x(), e->pos().y()};
    switch (e->button()) {
        case Qt::LeftButton:
            mouse.button = engine::Camera::Mouse::Button::Left;
            break;
        case Qt::RightButton:
            mouse.button = engine::Camera::Mouse::Button::Right;
            break;
        case Qt::MidButton:
            mouse.button = engine::Camera::Mouse::Button::Wheel;
            break;
        default:
            return;
    }
    m_renderer->processMousePress(mouse);
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

void OpenGLWidget::keyPressEvent(QKeyEvent *e) {}

void OpenGLWidget::wheelEvent(QWheelEvent *e) {
    m_renderer->processMouseScroll(float(e->delta()) / 240.f);
    update();
    setFocus();
}

void OpenGLWidget::setSelection(std::string s) {
    m_renderer->setSelection(std::move(s));
    emit selectionChanged();
}

void OpenGLWidget::addDrawable(engine::Drawable::Type type) {
    m_renderer->addDrawable(type);
    m_emitSceneTreeChanged = true;
    m_emitSelectionChanged = true;
}

void OpenGLWidget::removeSelection() {
    m_renderer->removeSelection();
    m_emitSceneTreeChanged = true;
    m_emitSelectionChanged = true;
}

void OpenGLWidget::emitSelectionChanged() {
    if (m_emitSelectionChanged) {
        m_emitSelectionChanged = false;
        emit selectionChanged();
    }
}

void OpenGLWidget::emitSceneTreeChanged() {
    if (m_emitSceneTreeChanged) {
        m_emitSceneTreeChanged = false;
        emit sceneTreeChanged();
    }
}
}  // namespace daft::app