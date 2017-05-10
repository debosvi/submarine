
macro(COMP_SRC_CHECK_VARS)
    if("${COMP_SRC_PROFILE}" STREQUAL "")
        message(SEND_ERROR "Unable to retreive component profile (variable COMP_SRC_PROFILE)")
    endif()
    
    if("${COMP_SRC_PROFILE}" STREQUAL "library")
        COMP_SRC_CHECK_VARS_LIBRARY()
        set(DO_GENERATE_LIB ON)
    elseif("${COMP_SRC_PROFILE}" STREQUAL "application")
        COMP_SRC_CHECK_VARS_APPLICATION()
        set(DO_GENERATE_APP ON)
    elseif("${COMP_SRC_PROFILE}" STREQUAL "test")
        COMP_SRC_CHECK_VARS_TEST()
        set(DO_GENERATE_TEST ON)
    else()
        message(SEND_ERROR "variable COMP_SRC_PROFILE is not yet managed, check documentation!)")
    endif()
    
endmacro()

macro(COMP_SRC_CHECK_VARS_LIBRARY)
    if("${COMP_SRC_LIB_TYPE}" STREQUAL "")
        message(SEND_ERROR "Unable to retreive library type (variable COMP_SRC_LIB_TYPE)")
    endif()
    
    if(NOT "${COMP_SRC_LIB_TYPE}" STREQUAL "both" AND NOT "${COMP_SRC_LIB_TYPE}" STREQUAL "static" AND NOT "${COMP_SRC_LIB_TYPE}" STREQUAL "shared")
        message(SEND_ERROR "Library type (must set to either 'static', 'shared' or 'both'")
    endif()
    
    if("${COMP_SRC_LIB_NAME}" STREQUAL "")
        message(SEND_ERROR "Unable to retreive library name (variable COMP_SRC_LIB_NAME)")
    endif()
    
    if("${LOCAL_SRC_FILES}" STREQUAL "")
        message(SEND_ERROR "Not any source files to build with (variable LOCAL_SRC_FILES)")
    endif()
endmacro()

macro(COMP_SRC_CHECK_VARS_APPLICATION)
    if("${COMP_SRC_APP_NAME}" STREQUAL "")
        message(SEND_ERROR "Unable to retreive application name (variable COMP_SRC_APP_NAME)")
    endif()
    
    if("${LOCAL_SRC_FILES}" STREQUAL "")
        message(SEND_ERROR "Not any source files to build with (variable LOCAL_SRC_FILES)")
    endif()
endmacro()

macro(COMP_SRC_CHECK_VARS_TEST)
    if("${COMP_SRC_TEST_NAME}" STREQUAL "")
        message(SEND_ERROR "Unable to retreive test output name (variable COMP_SRC_TEST_NAME)")
    endif()
    
    if("${LOCAL_SRC_FILES}" STREQUAL "")
        message(SEND_ERROR "Not any source files to build with (variable LOCAL_SRC_FILES)")
    endif()
endmacro()

