# - Try to find Jansson
# Once done this will define
#
#  Jansson_FOUND - system has Jansson
#  Jansson_INCLUDE_DIRS - the Jansson include directory
#  Jansson_LIBRARIES - Link these to use Jansson
#
#  Copyright (c) 2011 Lee Hambley <lee.hambley@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

if(Jansson_LIBRARIES AND Jansson_INCLUDE_DIRS)
    # in cache already
    set(Jansson_FOUND TRUE)
else()
    find_path(Jansson_INCLUDE_PATH
        NAMES jansson.h
        PATHS
            /usr/include
            /usr/local/include
            "$ENV{HOME}/usr/include"
        HINTS "${JANSSON_HINT_DIR}/include"
        DOC "Jansson header file"
    )
    
    
    if(NOT "${Jansson_INCLUDE_PATH}" STREQUAL "")
        set(Jansson_INCLUDE_DIRS ${Jansson_INCLUDE_PATH})
    endif()    

    find_library(Jansson_LIBRARY_PATH
        NAMES jansson
        PATHS
            /usr/lib
            /usr/local/lib
            "$ENV{HOME}/usr/lib"
        HINTS "${JANSSON_HINT_DIR}/lib"
        DOC "Jansson library"
    )

    if(NOT "${Jansson_LIBRARY_PATH}" STREQUAL "")
        get_filename_component(LIB_DIR ${Jansson_LIBRARY_PATH} DIRECTORY)
        get_filename_component(LIB_NAME ${Jansson_LIBRARY_PATH} NAME)
        set(Jansson_LIBRARY_DIRS ${LIB_DIR})
        set(Jansson_LIBRARIES ${LIB_NAME})
    endif()    

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(Jansson DEFAULT_MSG
        Jansson_INCLUDE_PATH
        Jansson_LIBRARY_PATH
    )

    # show the Jansson_INCLUDE_DIRS and Jansson_LIBRARIES variables only in the advanced view
    mark_as_advanced(
        Jansson_INCLUDE_PATH
        Jansson_LIBRARY_PATH
    )

endif()