cmake_minimum_required (VERSION 3.0)
project (J1939)

include(project_ver.cmake)

if("$ENV{SUBMARINE_PROJECT_DIR}" STREQUAL "")
    message(FATAL_ERROR "Please source root env.sh script")
endif()
    
include($ENV{SUBMARINE_PROJECT_DIR}/components/tools/ext-build/cmake/boz-build.cmake)

# include(CTest)
# set (CMAKE_VERBOSE_MAKEFILE ON)

include(tools.cmake)

include_directories(${CMAKE_SOURCE_DIR})

BOZ_COMPS_FIND_ALL("$ENV{SUBMARINE_PROJECT_DIR}/components/canbus/j1939")
BOZ_COMPS_FIND_ALL("${CMAKE_SOURCE_DIR}/sample")
