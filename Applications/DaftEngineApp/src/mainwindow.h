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
    void on_actionHDR_demo_triggered();
    void on_actionDir_Light_triggered();
    void on_actionSpot_Lights_triggered();
    void on_actionMetaballs_triggered();
    void on_actionProcedural_caves_triggered();

   private:
    void resizeEvent(QResizeEvent *event) override;

   private:
    Ui::MainWindow *ui;
};
}  // namespace daft::app