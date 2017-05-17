cmake_minimum_required (VERSION 3.0)
project (canprot)

include(project_ver.cmake)

if("$ENV{SUBMARINE_PROJECT_DIR}" STREQUAL "")
    message(FATAL_ERROR "Please source root env.sh script")
endif()
    
include($ENV{SUBMARINE_PROJECT_DIR}/components/tools/ext-build/cmake/boz-build.cmake)

# include(CTest)
# set (CMAKE_VERBOSE_MAKEFILE ON)

include(tools.cmake)

set(BOZ_ALL_COMPS_DIR "$ENV{SUBMARINE_PROJECT_DIR}/components")

if(${CYGWIN})
    add_definitions(-D__USE_CANUDP)
endif()

BOZ_COMPS_FIND_ALL("${BOZ_ALL_COMPS_DIR}/canbus")
BOZ_COMPS_FIND_ALL("${BOZ_ALL_COMPS_DIR}/canprot")
