#include <iostream>
#include <QtWidgets>
#include "MainWindow.hpp"
#define LOGURU_IMPLEMENTATION 1
#include "Server/loguru.hpp"
#include "CodeEditor.hpp"


int main(int argc, char *argv[]) {
    loguru::init(argc, argv);
    loguru::add_file("C_IDE_log.log", loguru::Append, loguru::Verbosity_MAX);
    LOG_F(INFO, "C! IDE started");
    QApplication a(argc, argv);
    MainWindow window;
    window.show();

//    CodeEditor editor;
//    editor.show();

    return a.exec();
}