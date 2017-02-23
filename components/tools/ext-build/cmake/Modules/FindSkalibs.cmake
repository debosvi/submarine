#.rst:
# FindCurses
# ----------
#
# Find the skalibs include file and library.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ``Skalibs_FOUND``
#   True if Skalibs is found.
# ``Skalibs_INCLUDE_DIRS``
#   The include directories needed to use Skalibs.
# ``Skalibs_LIBRARY_DIRS``
#   The include directories needed to use Skalibs.
# ``Skalibs_LIBRARIES``
#   The Skalibs library.

set(Skalibs_INCLUDE_DIRS)
set(Skalibs_LIBRARY_DIRS)
set(Skalibs_LIBRARIES)

find_path(Skalibs_INCLUDE_PATH
    NAMES skalibs/sysdeps.h
    PATHS /usr/include
        /usr/local/include
        "$ENV{HOME}/usr/include"
    HINTS "${SKALIBS_HINT_DIR}/include"
    DOC "Skalibs sysdeps"
    )

if(NOT "${Skalibs_INCLUDE_PATH}" STREQUAL "")
    set(Skalibs_INCLUDE_DIRS ${Skalibs_INCLUDE_PATH})
endif()    

find_library(Skalibs_LIBRARY_PATH
    NAMES skarnet
    PATHS /usr/lib
        /usr/local/lib
        "$ENV{HOME}/usr/lib"
    HINTS "${SKALIBS_HINT_DIR}/lib"
    PATH_SUFFIXES skalibs
    DOC "Skalibs library"
    )

if(NOT "${Skalibs_LIBRARY_PATH}" STREQUAL "")
    get_filename_component(LIB_DIR ${Skalibs_LIBRARY_PATH} DIRECTORY)
    get_filename_component(LIB_NAME ${Skalibs_LIBRARY_PATH} NAME)
    set(Skalibs_LIBRARY_DIRS ${LIB_DIR})
    set(Skalibs_LIBRARIES ${LIB_NAME})
endif()    

# handle the QUIETLY and REQUIRED arguments and set Skalibs_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Skalibs DEFAULT_MSG
    Skalibs_LIBRARY_PATH 
    Skalibs_INCLUDE_PATH
)

mark_as_advanced(
    Skalibs_INCLUDE_PATH
    Skalibs_LIBRARY_PATH
)