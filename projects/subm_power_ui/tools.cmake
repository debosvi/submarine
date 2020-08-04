
set(CMAKE_CXX_FLAGS "-fPIC")

find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)
include_directories(${Qt5SerialPort_INCLUDE_DIRS})
link_directories(${Qt5SerialPort_LIBRARY_DIRS})
include_directories(${Qt5Widgets_INCLUDE_DIRS})
link_directories(${Qt5Widgets_LIBRARY_DIRS})

find_package(Skalibs REQUIRED)

message(STATUS "Skalibs inc dir : ${Skalibs_INCLUDE_DIRS}")
message(STATUS "Skalibs link dir: ${Skalibs_LIBRARY_DIRS}")
message(STATUS "Skalibs libs dir: ${Skalibs_LIBRARIES}")

include_directories(${Skalibs_INCLUDE_DIRS})
link_directories(${Skalibs_LIBRARY_DIRS})


