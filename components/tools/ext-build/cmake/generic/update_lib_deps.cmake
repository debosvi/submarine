
## reinit variable since this script can be called several times
set(UPDATED_LIB_DEPS)
set(COMP_SRC_DEPS_PREFERRED)
set(LOCAL_LIB_DEPS_STATIC ${COMP_SRC_LIB_DEPS_STATIC})
set(LOCAL_LIB_DEPS_SHARED ${COMP_SRC_LIB_DEPS_SHARED})

if(NOT LOCAL_BUILD_STATIC AND NOT LOCAL_BUILD_SHARED)
    message(STATUS "Not any build type specified, prefer static")
    set(LOCAL_BUILD_STATIC ON)
    set(LOCAL_BUILD_SHARED OFF)
endif()

if(NOT "${COMP_SRC_LIB_DEPS}" STREQUAL "" AND "${COMP_SRC_DEPS_PREFERRED}" STREQUAL "")
    set(DEFAULT_LINK)
    if(LOCAL_BUILD_STATIC AND NOT LOCAL_BUILD_SHARED)
        set(DEFAULT_LINK "static")
    elseif(NOT LOCAL_BUILD_STATIC AND LOCAL_BUILD_SHARED)
        set(DEFAULT_LINK "shared")
    endif()
    
    if(DO_GENERATE_LIB)
        message(STATUS "No preferred library dependencies format for ${DEFAULT_LINK} library ${COMP_SRC_LIB_NAME}, use ${DEFAULT_LINK}")
    elseif(DO_GENERATE_APP)
        message(STATUS "No preferred library dependencies format for application ${COMP_SRC_APP_NAME}, use ${DEFAULT_LINK}")
    elseif(DO_GENERATE_TEST)
        message(STATUS "No preferred library dependencies format for test ${COMP_SRC_TEST_NAME}, use ${DEFAULT_LINK}")
    endif()
    set(COMP_SRC_DEPS_PREFERRED ${DEFAULT_LINK})
endif()

if("${COMP_SRC_DEPS_PREFERRED}" STREQUAL "static")
    list(APPEND LOCAL_LIB_DEPS_STATIC ${COMP_SRC_LIB_DEPS})
elseif("${COMP_SRC_DEPS_PREFERRED}" STREQUAL "shared")
    list(APPEND LOCAL_LIB_DEPS_SHARED ${COMP_SRC_LIB_DEPS})
endif()    

if(NOT "${LOCAL_LIB_DEPS_STATIC}" STREQUAL "")
    foreach(lib ${LOCAL_LIB_DEPS_STATIC})
        list(APPEND UPDATED_LIB_DEPS lib_${lib}_static)
    endforeach()
endif()

if(NOT "${LOCAL_LIB_DEPS_SHARED}" STREQUAL "")
    foreach(lib ${LOCAL_LIB_DEPS_SHARED})
        list(APPEND UPDATED_LIB_DEPS lib_${lib}_shared)
    endforeach()
endif()

## external lib deps 
list(APPEND UPDATED_LIB_DEPS ${COMP_EXT_LIB_DEPS})

if(DO_GENERATE_LIB)
    message(STATUS "List of updated dependencies for library ${COMP_SRC_LIB_NAME}: ${UPDATED_LIB_DEPS}")
elseif(DO_GENERATE_APP)
    message(STATUS "List of updated dependencies for application ${COMP_SRC_APP_NAME}: ${UPDATED_LIB_DEPS}")
elseif(DO_GENERATE_TEST)
    message(STATUS "List of updated dependencies for test ${COMP_SRC_TEST_NAME}: ${UPDATED_LIB_DEPS}")
endif()
