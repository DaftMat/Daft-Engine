//
// Created by mathis on 04/07/2020.
//
#pragma once
#include <Core/OpenGL.hpp>
#include <Minimal-Engine/Renderer.hpp>
#include <QOpenGLWidget>
#include <QtGui/QResizeEvent>

namespace daft::app {
/**
 * Widget holding the OpenGL context.
 */
class ENGINE_API OpenGLWidget : public QOpenGLWidget {
    Q_OBJECT

   public:
    /**
     * Standard constructor
     * @param parent - parent widget.
     */
    explicit OpenGLWidget(QWidget *parent = nullptr);

    /**
     * Destructor.
     */
    ~OpenGLWidget() override { cleanup(); }

    /**
     * renderer constant reference.
     * @return const ref to renderer.
     */
    [[nodiscard]] const Renderer &renderer() const { return *m_renderer; }

    /**
     * renderer reference.
     * @return ref to renderer.
     */
    Renderer &renderer() { return *m_renderer; }

    void emitNextFrame() { m_emitSelectionChanged = true; }

    void setSelection(std::string s);

    [[nodiscard]] QSize minimumSizeHint() const override { return {50, 50}; }

    [[nodiscard]] QSize sizeHint() const override { return {width(), height()}; }

    void mousePressEvent(QMouseEvent *e) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

    void mouseMoveEvent(QMouseEvent *e) override;

    void keyPressEvent(QKeyEvent *e) override;

    void wheelEvent(QWheelEvent *e) override;

   public slots:

    void cleanup() { m_renderer.reset(); }

   signals:

    void selectionChanged();

   protected:
    void initializeGL() override;

    void paintGL() override;

    void resizeGL(int width, int height) override;

    void prepareScene();

   private:
    void emitSelectionChanged();

    std::unique_ptr<Renderer> m_renderer{nullptr};

    bool m_glInitialized{false};
    bool m_emitSelectionChanged{false};
};
}  // namespace daft::app