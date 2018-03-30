#include <iostream>
#include <QtWidgets>
#include "MainWindow.hpp"
#include "CodeEditor.hpp"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow window;

    window.show();

//    CodeEditor editor;
//    editor.show();

    return a.exec();
}