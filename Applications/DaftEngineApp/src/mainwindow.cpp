#include "mainwindow.h"

#include <QtGui/QSurfaceFormat>
#include <QtWidgets/QMessageBox>
#include <sstream>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QSurfaceFormat format;
    format.setVersion(GL_MAJOR, GL_MINOR);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    ui->openGLWidget->setFocus();
    ui->openGLWidget->setFormat(format);
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
    ui->openGLWidget->resize(width() - 20, height());
}
