#include <Core/Utils/IO.hpp>
#include <QApplication>

#include "mainwindow.h"

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    a.setStyleSheet(daft::core::utils::IO::getStringFromFile("stylesheets/main.qss").c_str());

    daft::app::MainWindow w;
    w.show();

    return a.exec();
}