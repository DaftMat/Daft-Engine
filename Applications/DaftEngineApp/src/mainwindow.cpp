#include "mainwindow.h"

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

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    auto size = ui->centralwidget->borderLayout().regionSize(BorderLayout::Position::Center);
    ui->centralwidget->glWidget().resize(size.width(), size.height());
}
}  // namespace daft::app