set(CMAKE_SYSTEM_NAME Linux)

if("${GCC_PREFIX}" STREQUAL "")
        message(STATUS "Use GCC_PREFIX")
        set(GCC_PREFIX $ENV{JENKINS_HOME}/workspace)
endif()

message(STATUS "PREFIX: ${GCC_PREFIX}")

set(CMAKE_SYSROOT ${GCC_PREFIX}/cross/gcc-i486-linux-musl/)
set(CMAKE_STAGING_PREFIX /home/devel/stage)

set(CMAKE_C_COMPILER ${CMAKE_SYSROOT}/bin/i486-linux-musl-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_SYSROOT}/bin/i486-linux-musl-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# set(PRELOAD_S6 ON)