#define LOGURU_IMPLEMENTATION 1
#include <iostream>
#include <QtWidgets>
#include <GUI/MainWindow.hpp>
#include "Server/loguru.hpp"
#include <AST/CodeParser.hpp>
#include <GUI/CodeEditor.hpp>



int main(int argc, char *argv[]) {
    loguru::init(argc, argv);
    loguru::add_file("C_IDE_log.log", loguru::Truncate, loguru::Verbosity_INFO);
    LOG_F(INFO, "C! IDE started");
    QApplication a(argc, argv);
    MainWindow window;
    window.show();
    return QApplication::exec();

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

   /* //Pruebas con pointers
    prueba pb;
    int total = 1024;
    char* mem = (char*)malloc(sizeof(char)*total);
    int a = 8;
    int b = 5;
    double c = 5.2;
    float d = 10.222;
    char e = 2;
    long f = 999999;
    //char* dir_ptr_a = &*(mem + 0);
    char* dir_ptr_a = pb.storeInteger(8, 0, mem);
    //char* dir_ptr_c = &*(mem + sizeof(int));
    char* dir_ptr_c = pb.storeDouble(5.2, sizeof(int), mem);
    //char* dir_ptr_b = &*(mem + (sizeof(int) + sizeof(double)));
    char* dir_ptr_b = pb.storeInteger(5, (sizeof(int) + sizeof(double)), mem);

    char* dir_ptr_d = pb.storeFloat(10.222, (sizeof(int)*2 + sizeof(double)), mem);

    char* dir_ptr_e = pb.storeChar(2, (sizeof(int)*2 + sizeof(double) + sizeof(float)), mem);

    char* dir_ptr_f = pb.storeLong(999999, (sizeof(int)*2 + sizeof(double) + sizeof(float) + sizeof(char)), mem);
    //*dir_ptr_a = 8;
    //*dir_ptr_c = 3.2;
    //*dir_ptr_b = 5;
    std::cout << "a: " << a << " From mem: " << (int)*(mem) << std::endl;
    std::cout << "c: " << c << " From mem: " << (double)*(double*)(mem + sizeof(int)) << std::endl;
    std::cout << "b: " << b << " From mem: " << (int)*(mem + sizeof(int) + sizeof(double)) << std::endl;
    std::cout << "d: " << d << " From mem: " << (float)*(mem + sizeof(int)*2 + sizeof(double)) << std::endl;
    std::cout << "e: " << (int)e << " From mem: " << (int)*(mem + sizeof(int)*2 + sizeof(double) + sizeof(float))<< std::endl;
    std::cout << "f: " << f << " From mem: " << (long)*(mem + sizeof(int)*2 + sizeof(double) + sizeof(float) + sizeof(float)) << std::endl;

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
    m.setBegining(dir_ptr_c);

    std::cout << "Val stored in mem: " << *(double*)m.getBegining() << std::endl;

    MemoryNode mo;
    mo.setType("float");
    mo.setIdentifier("d");
    mo.setReferences(1);
    mo.setBegining(dir_ptr_d);

    std::cout << "Val stored in mem: " << *(float*)mo.getBegining() << std::endl;

    MemoryNode mi;
    mi.setType("char");
    mi.setIdentifier("e");
    mi.setReferences(1);
    mi.setBegining(dir_ptr_e);

    std::cout << "Val stored in mem: " << (int)*mi.getBegining() << std::endl;

    MemoryNode ma;
    ma.setType("long");
    ma.setIdentifier("f");
    ma.setReferences(1);
    ma.setBegining(dir_ptr_f);

    std::cout << "Val stored in mem: " << *(long*)ma.getBegining() << std::endl;*/


    /*void* memm = malloc(sizeof(char)*1024);
    int aa = 8;
    float bb = 5.555;
    double cc = 3.888;
    *(int*)((char*)memm + 0) = 8;
    *(float*)((char*)memm + sizeof(int)) = 3.555;
    *(double*)((char*)memm + (sizeof(int) + sizeof(float))) = 3.888;

    std::ostringstream oss;
    oss << (void const*)(float*)((char*)memm + sizeof(int));
    std::string s = oss.str();

    std::cout << "a: " << aa << " From mem: " << *(int*)((char*)memm + 0)
              << " Dir: " << &*(int*)((char*)memm + 0 )<< std::endl;
    std::cout << "b: " << bb << " From mem: " << *(float*)((char*)memm + sizeof(int))
              << " Dir: " << s << std::endl;
    std::cout << "c: " << cc << " From mem: " <<  *(double*)((char*)memm + (sizeof(int) + sizeof(float)))
              << " Dir: " << &*(double *)((char*)memm + sizeof(int) + sizeof(float)) << std::endl;*/
}



