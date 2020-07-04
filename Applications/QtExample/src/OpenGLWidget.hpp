//
// Created by mathis on 04/07/2020.
//
#pragma once
// clang-format off
#include <Minimal-Engine/Renderer.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
// clang-format on

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core {
    Q_OBJECT

   public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget() override { cleanup(); }

    [[nodiscard]] QSize minimumSizeHint() const override { return {50, 50}; }

    [[nodiscard]] QSize sizeHint() const override { return {1600, 900}; }

   public slots:
    void cleanup() { m_renderer.reset(); }

   protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    void prepareScene();

   private:
    std::unique_ptr<Renderer> m_renderer{nullptr};

    bool m_glInitialized{false};
};
