//
// Created by mathis on 04/07/2020.
//
#pragma once
#include <Core/OpenGL.hpp>
#include <Engine/Renderer/Renderer.hpp>
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
    ~OpenGLWidget() override;

    /**
     * renderer constant reference.
     * @return const ref to renderer.
     */
    [[nodiscard]] const engine::Renderer &renderer() const { return *m_renderer; }

    /**
     * renderer reference.
     * @return ref to renderer.
     */
    engine::Renderer &renderer() { return *m_renderer; }

    /**
     * Tells the gl widget to emit a signal on the next frame.
     */
    void emitNextFrame() { m_emitSelectionChanged = true; }

    /**
     * Selected Drawable setter.
     * @param s - name of the selected drawable.
     */
    void setSelection(std::string s);

    /**
     * Adds a drawable to the scene.
     * @param type - type of the new drawable to add.
     */
    void addDrawable(engine::Drawable::Type type, glm::vec3 pos = glm::vec3{0.f}, glm::vec3 rot = glm::vec3{0.f},
                     glm::vec3 scale = glm::vec3{1.f}, core::SettingManager sm = core::SettingManager{});

    void addCustomObject(std::string filePath, glm::vec3 pos = glm::vec3{0.f}, glm::vec3 rot = glm::vec3{0.f},
                         glm::vec3 scale = glm::vec3{1.f});

    /**
     * Removes the selected drawable from the scene.
     */
    void removeSelection();

    [[nodiscard]] QSize minimumSizeHint() const override { return {50, 50}; }
    [[nodiscard]] QSize sizeHint() const override { return {width(), height()}; }

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

   public slots:
    void cleanup();

   signals:
    void selectionChanged();
    void sceneTreeChanged();
    void glInitialized();

   protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void prepareScene();

   private:
    void emitSelectionChanged();
    void emitSceneTreeChanged();

    std::unique_ptr<engine::Renderer> m_renderer{nullptr};

    bool m_glInitialized{false};
    bool m_emitSelectionChanged{false};
    bool m_emitSceneTreeChanged{false};
};
}  // namespace daft::app