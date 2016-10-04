cmake_minimum_required(VERSION 3.0)

project(SubmarineUI)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

include_directories(include)

# Tell CMake to create the helloworld executable
add_executable(SubmarineUI 
    src/mainwindow.cpp
    src/main.cpp
    )

# Use the Widgets module from Qt 5.
target_link_libraries(SubmarineUI Qt5::Widgets)