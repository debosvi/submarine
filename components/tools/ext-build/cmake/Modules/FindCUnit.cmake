#.rst:
# FindSkalibs
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
#   True if CUnit is found.
# ``CUnit_INCLUDE_DIRS``
#   The include directories needed to use CUnit.
# ``CUnit_LIBRARY_DIRS``
#   The include directories needed to use CUnit.
# ``CUnit_LIBRARIES``
#   The CUnit library.

set(CUnit_INCLUDE_DIRS)
set(CUnit_LIBRARY_DIRS)
set(CUnit_LIBRARIES)

find_path(CUnit_INCLUDE_PATH
    NAMES CUnit/CUnit.h
    PATHS /usr/include
        /usr/local/include
        "$ENV{HOME}/usr/include"
    HINTS "${SKALIBS_HINT_DIR}/include"
    DOC "CUnit header"
    )

if(NOT "${CUnit_INCLUDE_PATH}" STREQUAL "")
    set(CUnit_INCLUDE_DIRS ${CUnit_INCLUDE_PATH})
endif()    

find_library(CUnit_LIBRARY_PATH
    NAMES cunit
    PATHS /usr/lib
        /usr/local/lib
        "$ENV{HOME}/usr/lib"
    HINTS "${SKALIBS_HINT_DIR}/lib"
    PATH_SUFFIXES skalibs
    DOC "CUnit library"
    )

if(NOT "${CUnit_LIBRARY_PATH}" STREQUAL "")
    get_filename_component(LIB_DIR ${CUnit_LIBRARY_PATH} DIRECTORY)
    get_filename_component(LIB_NAME ${CUnit_LIBRARY_PATH} NAME)
    set(CUnit_LIBRARY_DIRS ${LIB_DIR})
    set(CUnit_LIBRARIES ${LIB_NAME})
endif()    

# handle the QUIETLY and REQUIRED arguments and set CUnit_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CUnit DEFAULT_MSG
    CUnit_LIBRARY_PATH 
    CUnit_INCLUDE_PATH
)

mark_as_advanced(
    CUnit_INCLUDE_PATH
    CUnit_LIBRARY_PATH
)
