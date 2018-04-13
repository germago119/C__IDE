#define LOGURU_IMPLEMENTATION 1
#include <iostream>
#include <QtWidgets>
#include <GUI/MainWindow.hpp>
#include "Server/loguru.hpp"
#include <AST/CodeParser.hpp>
#include <GUI/CodeEditor.hpp>
#include <DataStructures/SimpleLinkedList.h>

int main(int argc, char *argv[]) {
    loguru::init(argc, argv);
    loguru::add_file("C_IDE_log.log", loguru::Truncate, loguru::Verbosity_INFO);
    LOG_F(INFO, "C! IDE started");
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();

    /*SimpleLinkedList<int> list_1;
    int data;
    int index;

    cout << "Agrega un elemento por la cabeza: " << endl;
    std::cin >> data;
    list_1.insertFront(data);

    cout << "Agrega un elemento por la cabeza: " << endl;
    std::cin >> data;
    list_1.insertFront(data);

    cout << "Agrega un elemento por la cabeza: " << endl;
    std::cin >> data;
    list_1.insertFront(data);

    cout << "Agrega un elemento por la cola: " << endl;
    std::cin >> data;
    list_1.insertRear(data);

    cout << "Agrega un elemento por la cola: " << endl;
    std::cin >> data;
    list_1.insertRear(data);

    cout << "Agrega un elemento por la indice: " << endl;
    std::cin >> data;
    cout << "Indice: " << endl;
    std::cin >> index;
    list_1.insertByIndex(data, index);

    cout << "Agrega un elemento por la indice: " << endl;
    std::cin >> data;
    cout << "Indice: " << endl;
    std::cin >> index;
    list_1.insertByIndex(data, index);

    cout << "Elimina un elemento por la indice: " << endl;
    std::cin >> index;
    list_1.deleteByIndex(index);

    cout << "Elimina cola: " << endl;
    list_1.deleteRear();

    cout << "Agrega un elemento por la indice: " << endl;
    std::cin >> data;
    cout << "Indice: " << endl;
    std::cin >> index;
    list_1.insertByIndex(data, index);

    cout << "Elimina cabeza: " << endl;
    list_1.deleteFront();

    cout << "Elimina un elemento por la indice: " << endl;
    std::cin >> index;
    list_1.deleteByIndex(index);

    return 0;*/
}

