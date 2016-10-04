cmake_minimum_required(VERSION 3.0)

project(SubmarineUI)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC OFF)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

include_directories(include)

qt5_generate_moc(include/mainwindow.h moc_mainwindow.cpp)

# Tell CMake to create the helloworld executable
add_executable(SubmarineUI WIN32 
    src/mainwindow.cpp
    src/main.cpp
    moc_mainwindow.cpp
    )

# Use the Widgets module from Qt 5.
target_link_libraries(SubmarineUI Qt5::Widgets)