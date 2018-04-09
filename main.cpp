#include <iostream>
#include <QtWidgets>
#include <AST/NodePrefix.hpp>
#include <MainWindow.hpp>
#include "GUI/MainWindow.hpp"
#define LOGURU_IMPLEMENTATION 1

#include <Server/loguru.hpp>
#include <CodeEditor.hpp>
#include "Server/loguru.hpp"
#include "GUI/CodeEditor.hpp"


//int main(int argc, char *argv[]) {
//    loguru::init(argc, argv);
//    loguru::add_file("C_IDE_log.log", loguru::Truncate, loguru::Verbosity_INFO);
//    LOG_F(INFO, "C! IDE started");
//    QApplication a(argc, argv);
//    MainWindow window;
//    window.show();
//    return a.exec();
//}

int main() {

    std::cout << "int A = 6" << std::endl;
    NodePrefix("int A = 6");
    std::cout << "\n\n\n\n\n\"" "float b = 7" << std::endl;
    NodePrefix("float b = 7");
    std::cout << "\n\n\n\n\n\"" "char c = 'c'" << std::endl;
    NodePrefix("char c = 'c'");
    std::cout << "\n\n\n\n\n\""  "b * a" << std::endl;
    NodePrefix("b * a");
    std::cout << "\n\n\n\n\n\""  "c / d" << std::endl;
    NodePrefix("c / d");
    return 0;


int main(int argc, char *argv[]) {
    loguru::init(argc, argv);
    loguru::add_file("C_IDE_log.log", loguru::Truncate, loguru::Verbosity_INFO);
    LOG_F(INFO, "C! IDE started");
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();

   /* JSONparser *parser;
    QJsonDocument receivedData = parser->writeMallocRequest(100);
    QString jsonString = receivedData.toJson(QJsonDocument::Compact);
    std::cout << jsonString.toStdString() << std::endl;*/
}