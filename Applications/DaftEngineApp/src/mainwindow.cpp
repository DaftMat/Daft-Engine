#include "mainwindow.h"

#include <Core/Random.hpp>
#include <Layouts/BorderLayout.hpp>
#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QMessageBox>
#include <sstream>

#include "ui_mainwindow.h"

namespace daft::app {
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new ::Ui::MainWindow) {
    ui->setupUi(this);

    QSurfaceFormat format;
    format.setVersion(GL_MAJOR, GL_MINOR);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSamples(32);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    ui->centralwidget->glWidget().setFocus();
    ui->centralwidget->glWidget().setFormat(format);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionOpenGL_triggered() {
    std::stringstream message;
    message << "Renderer\t: " << glGetString(GL_RENDERER) << std::endl;
    message << "Vendor\t: " << glGetString(GL_VENDOR) << std::endl;
    message << "Version\t: " << glGetString(GL_VERSION) << std::endl;
    message << "GLSL\t: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    message << "Qt\t: " << qVersion() << std::endl;
    QMessageBox::information(this, "OpenGL Information", message.str().c_str());
}

void MainWindow::on_actionHDR_demo_triggered() {}

void MainWindow::on_actionDir_Light_triggered() {
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::DirLight, glm::vec3{0.f}, {40.f, 0.f, 0.f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::Torus);
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::Cube, {0.f, -0.6f, 0.f}, glm::vec3{0.f},
                                              {100.f, 0.05f, 100.f});
    for (int i = 0; i < 512; ++i) {
        ui->centralwidget->glWidget().addDrawable(
            engine::Drawable::Type::Cube, {core::Random::get(-100.f, 100.f), 3.f, core::Random::get(-100.f, 100.f)},
            {core::Random::get(-30.f, 30.f), 0.f, core::Random::get(-30.f, 30.f)}, {0.3f, 5.f, 0.3f});
    }
    ui->centralwidget->glWidget().update();
}

void MainWindow::on_actionSpot_Lights_triggered() {}

void MainWindow::on_actionMetaballs_triggered() {
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::Metaballs);
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::DirLight, glm::vec3{0.f}, {40.f, 0.f, 0.f});
    ui->centralwidget->glWidget().update();
}

void MainWindow::on_actionProcedural_caves_triggered() {}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    auto size = ui->centralwidget->borderLayout().regionSize(BorderLayout::Position::Center);
    ui->centralwidget->glWidget().resize(size.width(), size.height());
}
}  // namespace daft::app