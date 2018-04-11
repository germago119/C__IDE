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


find_package(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK ON) # force dynamic linking for all libraries


add_executable(C__IDE main.cpp GUI/MainWindow.cpp GUI/MainWindow.hpp Server/LocalServer.cpp Server/LocalServer.h GUI/CodeEditor.cpp GUI/CodeEditor.hpp GUI/Highlighter.cpp GUI/Highlighter.hpp JSON/JSONparser.cpp JSON/JSONparser.h AST/CodeParser.cpp AST/CodeParser.hpp AST/NodeToken.cpp AST/NodeToken.hpp AST/JSONVar.cpp AST/JSONVar.hpp AST/JSONStruct.cpp AST/JSONStruct.hpp)
target_link_libraries(C__IDE Qt5::Widgets Qt5::Core Qt5::Network)

#Necesario para libreria de logging
find_package(Threads)
target_link_libraries(C__IDE ${CMAKE_THREAD_LIBS_INIT}) # For pthreads
target_link_libraries(C__IDE dl) # For ldl


target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
