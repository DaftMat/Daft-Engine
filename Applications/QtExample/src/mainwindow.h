#pragma once
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:
    void on_actionOpenGL_triggered();
    void on_openGLWidget_resized();

   private:
    Ui::MainWindow *ui;
};
