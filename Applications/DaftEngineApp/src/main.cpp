#include <Core/Utils/Log.hpp>
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv) {
    daft::core::utils::Log::init();

    QApplication a(argc, argv);
    daft::app::MainWindow w;
    w.show();

    return a.exec();
}