cmake_minimum_required(VERSION 3.9)
project(C__IDE)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/Applications/Qt/5.10.1/clang_64")

set( CMAKE_INCLUDE_CURRENT_DIR ON )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Sql REQUIRED)

#qt5_wrap_ui(UI_HEADERS mainwindow.ui)
#qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

#qt5_add_resources( QRCS resources.qrc )
add_executable(C__IDE main.cpp GUI/MainWindow.cpp GUI/MainWindow.hpp Server/LocalServer.cpp GUI/CodeEditor.cpp GUI/CodeEditor.hpp GUI/Highlighter.cpp GUI/Highlighter.hpp AST/ASCIIParser.cpp AST/ASCIIParser.hpp AST/NodeType.cpp AST/NodeType.hpp JSON/JSONparser.cpp JSON/JSONparser.h AST/NodePrefix.cpp)
target_link_libraries(C__IDE Qt5::Widgets Qt5::Core Qt5::Network Qt5::Sql Qt5::OpenGL)

#Necesario para libreria de logging
find_package(Threads)
target_link_libraries(C__IDE ${CMAKE_THREAD_LIBS_INIT}) # For pthreads
target_link_libraries(C__IDE dl) # For ldl