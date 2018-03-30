#include <iostream>
#include <QtWidgets>
#include "MainWindow.hpp"
#define LOGURU_IMPLEMENTATION 1
#include "Server/loguru.hpp"

int main(int argc, char *argv[]) {
    loguru::init(argc, argv);
    loguru::add_file("everything.log", loguru::Append, loguru::Verbosity_MAX);
    LOG_F(INFO, "C! IDE started");
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();
}