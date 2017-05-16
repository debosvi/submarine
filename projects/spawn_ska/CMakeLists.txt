cmake_minimum_required (VERSION 3.0)
project (spawn_ska)

include(project_ver.cmake)

if("$ENV{SUBMARINE_PROJECT_DIR}" STREQUAL "")
    message(FATAL_ERROR "Please source root env.sh script")
endif()
    
include($ENV{SUBMARINE_PROJECT_DIR}/components/tools/ext-build/cmake/boz-build.cmake)

# include(CTest)
# set (CMAKE_VERBOSE_MAKEFILE ON)

include(tools.cmake)

set(BOZ_ALL_COMPS_DIR "$ENV{SUBMARINE_PROJECT_DIR}/components")

add_definitions(-DBOZ_ALL_COMPS_DIR=${BOZ_ALL_COMPS_DIR})

if(${CYGWIN})
    add_definitions(-D__USE_CANUDP)
endif()
BOZ_COMPS_FIND_ALL("${BOZ_ALL_COMPS_DIR}/spawn")
BOZ_COMPS_FIND_ALL("${BOZ_ALL_COMPS_DIR}/canbus")
