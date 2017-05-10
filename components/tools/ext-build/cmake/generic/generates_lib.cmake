
set(LOCAL_TYPE_STATIC OFF)
set(LOCAL_TYPE_SHARED OFF)

if("${COMP_SRC_LIB_TYPE}" STREQUAL "both")
    set(LOCAL_TYPE_STATIC ON)
    set(LOCAL_TYPE_SHARED ON)
elseif("${COMP_SRC_LIB_TYPE}" STREQUAL "static")
    set(LOCAL_TYPE_STATIC ON)
elseif("${COMP_SRC_LIB_TYPE}" STREQUAL "shared")
    set(LOCAL_TYPE_SHARED ON)
endif()

## build static lib
set(LOCAL_BUILD_STATIC ON)
set(LOCAL_BUILD_SHARED OFF)
include(${BOZ_EXT_BUILD_DIR}/generic/update_lib_deps.cmake)
    
## build static library
if(${LOCAL_TYPE_STATIC})
    add_library(lib_${COMP_SRC_LIB_NAME}_static 
        STATIC 
        # EXCLUDE_FROM_ALL
        ${UPDATED_SRC_FILES}
        )
    set_target_properties(lib_${COMP_SRC_LIB_NAME}_static PROPERTIES OUTPUT_NAME ${COMP_SRC_LIB_NAME})
    if(NOT "${UPDATED_LIB_DEPS}" STREQUAL "")
        target_link_libraries(lib_${COMP_SRC_LIB_NAME}_static PUBLIC ${UPDATED_LIB_DEPS})
    endif()
    BOZ_INSTALL_ITEM(lib_${COMP_SRC_LIB_NAME}_static)
endif()

## build shared lib
set(LOCAL_BUILD_STATIC OFF)
set(LOCAL_BUILD_SHARED ON)
include(${BOZ_EXT_BUILD_DIR}/generic/update_lib_deps.cmake)

## build shared library
if(${LOCAL_TYPE_SHARED})
    add_library(lib_${COMP_SRC_LIB_NAME}_shared
        # EXCLUDE_FROM_ALL
        ${UPDATED_SRC_FILES}
        )

    set_target_properties(lib_${COMP_SRC_LIB_NAME}_shared PROPERTIES OUTPUT_NAME ${COMP_SRC_LIB_NAME})
    if(NOT "${UPDATED_LIB_DEPS}" STREQUAL "")
        target_link_libraries(lib_${COMP_SRC_LIB_NAME}_shared PUBLIC ${UPDATED_LIB_DEPS})
    endif()
    
    if(${MINGW})
        set_target_properties(lib_${COMP_SRC_LIB_NAME}_shared
                      PROPERTIES SUFFIX ".dll")
    elseif(${UNIX})
        set_target_properties(lib_${COMP_SRC_LIB_NAME}_shared
                      PROPERTIES SUFFIX ".so")
    endif()
    
    BOZ_INSTALL_ITEM(lib_${COMP_SRC_LIB_NAME}_shared)
endif()
