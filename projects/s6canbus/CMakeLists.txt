cmake_minimum_required (VERSION 3.0)
project (s6canbus)

include(project_ver.cmake)

if("$ENV{SUBMARINE_PROJECT_DIR}" STREQUAL "")
    message(FATAL_ERROR "Please source root env.sh script")
endif()
    
include($ENV{SUBMARINE_PROJECT_DIR}/components/tools/ext-build/cmake/boz-build.cmake)

# include(CTest)
# set (CMAKE_VERBOSE_MAKEFILE ON)

include(tools.cmake)

BOZ_COMPS_FIND_ALL("$ENV{SUBMARINE_PROJECT_DIR}/components/canbus/s6canbus")
BOZ_COMPS_FIND_ALL("$ENV{SUBMARINE_PROJECT_DIR}/components/misc/tools")
