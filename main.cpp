#define LOGURU_IMPLEMENTATION 1
#include <iostream>
#include <QtWidgets>
#include <GUI/MainWindow.hpp>
#include "Server/loguru.hpp"
#include <AST/CodeParser.hpp>
#include <GUI/CodeEditor.hpp>
#include <prueba.h>


int main(int argc, char *argv[]) {
/*    loguru::init(argc, argv);
    loguru::add_file("C_IDE_log.log", loguru::Truncate, loguru::Verbosity_INFO);
    LOG_F(INFO, "C! IDE started");
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();*/

/*    QJsonObject obj;
    obj.insert("Value", "2");
    QJsonDocument doc(obj);

    QJsonObject obj2 = doc.object();

    try {
        int val = boost::lexical_cast<int>(obj2.value("Value").toString().toStdString());
        std::cout << "Value: " << val << std::endl;
    } catch( boost::bad_lexical_cast const& ) {
        std::cout << "Error: input string was not valid" << std::endl;
    }
    //int val = obj2.value("Value").toInt();*/

    /*int *val = (int *) malloc(sizeof(int));
    val[0] = 8;
    std::cout << "Value from pointer: " << *val << std::endl;

    int i = 9;
    char* a = (char*)&i;*/

    //Pruebas con pointers
    prueba pb;
    int total = 1024;
    char* mem = (char*)malloc(sizeof(char)*total);
    int a = 8;
    int b = 5;
    double c = 5.2;
    //char* dir_ptr_a = &*(mem + 0);
    char* dir_ptr_a = pb.storeInteger(8, 0, mem);
    //char* dir_ptr_c = &*(mem + sizeof(int));
    char* dir_ptr_c = pb.storeDouble(5.2, sizeof(int), mem);
    //char* dir_ptr_b = &*(mem + (sizeof(int) + sizeof(double)));
    char* dir_ptr_b = pb.storeInteger(5, (sizeof(int) + sizeof(double)), mem);
    //*dir_ptr_a = 8;
    //*dir_ptr_c = 3.2;
    //*dir_ptr_b = 5;
    std::cout << "a: " << a << " From mem: " << *(int*)dir_ptr_a << std::endl;
    std::cout << "c: " << c << " From mem: " << *(double*)dir_ptr_c << std::endl;
    std::cout << "b: " << b << " From mem: " << *(int*)dir_ptr_b << std::endl;

    MemoryNode memoryNode;
    memoryNode.setType("int");
    memoryNode.setIdentifier("a");
    memoryNode.setReferences(1);
    memoryNode.setBegining(dir_ptr_a);

    std::cout << "Val stored in mem: " << *(int*)memoryNode.getBegining() << std::endl;

    MemoryNode memory;
    memory.setType("int");
    memory.setIdentifier("b");
    memory.setReferences(1);
    memory.setBegining(dir_ptr_b);

    std::cout << "Val stored in mem: " << *(int*)memory.getBegining() << std::endl;

    MemoryNode m;
    m.setType("double");
    m.setIdentifier("c");
    m.setReferences(1);
    m.setBegining(dir_ptr_b);

    std::cout << "Val stored in mem: " << *(double*)m.getBegining() << std::endl;

    double e = *(double*)dir_ptr_c;
    std::cout << e << std::endl;
}



