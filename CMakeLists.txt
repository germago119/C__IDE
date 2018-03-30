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

#qt5_wrap_ui( UI_HEADERS mainwindow.ui )
qt5_wrap_ui(UI_GENERATED_HEADERS ${UI_SOURCES})

#qt5_add_resources( QRCS resources.qrc )
add_executable(C__IDE main.cpp MainWindow.cpp MainWindow.hpp NetSocket.cpp NetSocket.hpp NetServer.cpp NetServer.hpp)
target_link_libraries(C__IDE Qt5::Widgets Qt5::Core Qt5::Network Qt5::Sql Qt5::OpenGL)