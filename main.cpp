#include <iostream>
#include <QtWidgets>
#include <AST/NodePrefix.hpp>
#include "GUI/MainWindow.hpp"
#define LOGURU_IMPLEMENTATION 1

#include <Server/loguru.hpp>
#include "GUI/CodeEditor.hpp"


/*int main() {

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
}*/

int main(int argc, char *argv[]) {
    loguru::init(argc, argv);
    loguru::add_file("C_IDE_log.log", loguru::Truncate, loguru::Verbosity_INFO);
    LOG_F(INFO, "C! IDE started");
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return a.exec();

    /*JSONparser *parser;
    QJsonDocument receivedData = parser->writeRAMdata(0, "a", "b", 2);
    std::cout << receivedData.toJson(QJsonDocument::Compact).toStdString()<< std::endl;
    QJsonObject json = receivedData.object();
    if (json.contains("Subject") && json["Subject"] == "RAM") {
        QJsonArray contents = json["Contents"].toArray();

        std::cout << contents[0].toObject().value("Direction").toString().toStdString() << std::endl;
        std::cout << contents[0].toObject().value("Name").toString().toStdString() << std::endl;
        std::cout << contents[0].toObject().value("Value").toString().toStdString() << std::endl;
        std::cout << contents[0].toObject().value("References").toString().toStdString() << std::endl;
    } else
        std::cout << "no" << std::endl;*/
}
