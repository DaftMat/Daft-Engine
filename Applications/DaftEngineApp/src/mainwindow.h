#pragma once
#include <QMainWindow>
#include <QResizeEvent>

namespace Ui {
class MainWindow;
}

namespace daft::app {
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

   private slots:

    void on_actionOpenGL_triggered();
    void on_actionOpen_Sky_Surface_triggered();
    void on_actionClosed_Space_triggered();
    void on_actionShadow_Maps_demo_triggered();

   private:
    void resizeEvent(QResizeEvent *event) override;

   private:
    Ui::MainWindow *ui;
};
}  // namespace daft::app