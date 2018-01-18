cmake_minimum_required (VERSION 3.0)
project (s6canbus)

include(project_ver.cmake)

set(PRJ_DIR $ENV{SUBMARINE_PROJECT_DIR})
if("${PRJ_DIR}" STREQUAL "")
    set(PRJ_DIR ${SUBMARINE_PROJECT_DIR})
endif()
if("${PRJ_DIR}" STREQUAL "")
    message(FATAL_ERROR "Please source root env.sh script")
endif()

include(${PRJ_DIR}/components/tools/ext-build/cmake/boz-build.cmake)

# include(CTest)
# set (CMAKE_VERBOSE_MAKEFILE ON)

include(tools.cmake)

BOZ_COMPS_FIND_ALL("${PRJ_DIR}/components/canbus/base")
# BOZ_COMPS_FIND_ALL("${PRJ_DIR}/components/canbus/fillbuf")
BOZ_COMPS_FIND_ALL("${PRJ_DIR}/components/canbus/candev")


# BOZ_COMPS_FIND_ALL("${PRJ_DIR}/components/canbus/canmsg")
# BOZ_COMPS_FIND_ALL("${PRJ_DIR}/components/canbus/s6canbus")

#BOZ_COMPS_FIND_ALL("${PRJ_DIR}/components/misc/tools")
