#define __gl3_h_

#include <Core/Utils/Log.hpp>
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv) {
    stardust::core::utils::Log::init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}