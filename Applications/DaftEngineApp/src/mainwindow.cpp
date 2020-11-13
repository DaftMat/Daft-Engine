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

void MainWindow::on_actionOpen_Sky_Surface_triggered() {
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::BSpline2D);
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::DirLight);
    core::SettingManager smRed;
    smRed.add("Color", glm::vec3{0.8f, 0.f, 0.f});
    core::SettingManager smGreen;
    smGreen.add("Color", glm::vec3{0.f, 0.8f, 0.f});
    core::SettingManager smBlue;
    smBlue.add("Color", glm::vec3{0.f, 0.f, 0.8f});
    core::SettingManager smCyan;
    smCyan.add("Color", glm::vec3{0.f, 0.8f, 0.8f});
    core::SettingManager smMagenta;
    smMagenta.add("Color", glm::vec3{0.8f, 0.f, 0.8f});
    core::SettingManager smYellow;
    smYellow.add("Color", glm::vec3{0.8f, 0.8f, 0.f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight,
                                              {core::Random::get(-6, 6), 1.2, core::Random::get(-6, 6)}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smRed));
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight,
                                              {core::Random::get(-6, 6), 1.2, core::Random::get(-6, 6)}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smGreen));
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight,
                                              {core::Random::get(-6, 6), 1.2, core::Random::get(-6, 6)}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smBlue));
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight,
                                              {core::Random::get(-6, 6), 1.2, core::Random::get(-6, 6)}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smCyan));
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight,
                                              {core::Random::get(-6, 6), 1.2, core::Random::get(-6, 6)}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smMagenta));
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight,
                                              {core::Random::get(-6, 6), 1.2, core::Random::get(-6, 6)}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smYellow));
    ui->centralwidget->glWidget().update();
}

void MainWindow::on_actionClosed_Space_triggered() {
    core::SettingManager smTorus;
    smTorus.add("Meridians", 110);
    smTorus.add("Parallels", 80);
    smTorus.add("Inner Radius", 2.f);
    smTorus.add("Outer Radius", 0.1f);
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::Torus, glm::vec3{0.f}, {90.f, 0.f, 0.f},
                                              {1.f, 40.f, 1.f}, std::move(smTorus));

    core::SettingManager smCube;
    smCube.add("Resolution", 4);
    smCube.add("Radius", 2.f);
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::Cube, {0.f, 0.f, -4.1f}, glm::vec3{0.f},
                                              {1.f, 1.f, 0.1f}, std::move(smCube));

    core::SettingManager smWhite;
    smWhite.add("Color", glm::vec3{5.f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight, {0.f, 0.f, -3.5f}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smWhite));

    core::SettingManager smRed;
    smRed.add("Color", glm::vec3{0.8f, 0.f, 0.f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight, {1.7f, 0.f, -1.f}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smRed));

    core::SettingManager smGreen;
    smGreen.add("Color", glm::vec3{0.f, 0.8f, 0.f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight, {0.f, 1.8f, 0.f}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smGreen));

    core::SettingManager smBlue;
    smBlue.add("Color", glm::vec3{0.f, 0.f, 0.8f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight, {-1.7f, 0.f, -2.f}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smBlue));

    core::SettingManager smCyan;
    smCyan.add("Color", glm::vec3{0.f, 0.8f, 0.8f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight, {0.f, -1.8f, 1.f}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smCyan));

    core::SettingManager smMagenta;
    smMagenta.add("Color", glm::vec3{0.8f, 0.f, 0.8f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight, {1.3f, 1.3f, 2.f}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smMagenta));

    core::SettingManager smYellow;
    smYellow.add("Color", glm::vec3{0.8f, 0.8f, 0.f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::PointLight, {-1.3f, -1.3f, 3.f}, glm::vec3{0.f},
                                              glm::vec3{1.f}, std::move(smYellow));

    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::DirLight);
}

void MainWindow::on_actionShadow_Maps_demo_triggered() {
    core::SettingManager smCyan;
    smCyan.add("Color", glm::vec3{0.f, 5.f, 5.f});
    smCyan.add("Intensity", 10.f);
    smCyan.add("Inner angle", 25.f);
    smCyan.add("Outer angle", 30.f);
    ui->centralwidget->glWidget().addDrawable(
        engine::Drawable::Type::SpotLight, {core::Random::get(-20.f, 20.f), 11.f, core::Random::get(-20.f, 20.f)},
        {core::Random::get(-35.f, 35.f), 0.f, core::Random::get(-35.f, 35.f)}, glm::vec3{1.f}, std::move(smCyan));

    core::SettingManager smMagenta;
    smMagenta.add("Color", glm::vec3{5.f, 0.f, 5.f});
    smMagenta.add("Intensity", 10.f);
    smMagenta.add("Inner angle", 25.f);
    smMagenta.add("Outer angle", 30.f);
    ui->centralwidget->glWidget().addDrawable(
        engine::Drawable::Type::SpotLight, {core::Random::get(-20.f, 20.f), 11.f, core::Random::get(-20.f, 20.f)},
        {core::Random::get(-35.f, 35.f), 0.f, core::Random::get(-35.f, 35.f)}, glm::vec3{1.f}, std::move(smMagenta));

    core::SettingManager smYellow;
    smYellow.add("Color", glm::vec3{5.f, 5.f, 0.f});
    smYellow.add("Intensity", 10.f);
    smYellow.add("Inner angle", 25.f);
    smYellow.add("Outer angle", 30.f);
    ui->centralwidget->glWidget().addDrawable(
        engine::Drawable::Type::SpotLight, {core::Random::get(-20.f, 20.f), 11.f, core::Random::get(-20.f, 20.f)},
        {core::Random::get(-35.f, 35.f), 0.f, core::Random::get(-35.f, 35.f)}, glm::vec3{1.f}, std::move(smYellow));

    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::DirLight, glm::vec3{0.f}, {40.f, 0.f, 0.f});
    ui->centralwidget->glWidget().addDrawable(engine::Drawable::Type::Cube, {0.f, -0.6f, 0.f}, glm::vec3{0.f},
                                              {30.f, 0.05f, 30.f});
    for (int i = 0; i < 64; ++i) {
        ui->centralwidget->glWidget().addDrawable(
            engine::Drawable::Type::Cube, {core::Random::get(-30.f, 30.f), 3.f, core::Random::get(-30.f, 30.f)},
            {core::Random::get(-30.f, 30.f), 0.f, core::Random::get(-30.f, 30.f)}, {0.3f, 5.f, 0.3f});
    }
    ui->centralwidget->glWidget().update();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    auto size = ui->centralwidget->borderLayout().regionSize(BorderLayout::Position::Center);
    ui->centralwidget->glWidget().resize(size.width(), size.height());
}
}  // namespace daft::app