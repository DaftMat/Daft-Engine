#pragma once
#include <QMainWindow>
#include <QResizeEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

   private slots:
    void on_actionOpenGL_triggered();

   private:
    void resizeEvent(QResizeEvent *event) override;

   private:
    Ui::MainWindow *ui;
};
