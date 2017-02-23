
set(LOCAL_BUILD_STATIC OFF)
set(LOCAL_BUILD_SHARED ON)
include(${BOZ_EXT_BUILD_DIR}/generic/update_lib_deps.cmake)

add_executable(app_${COMP_SRC_APP_NAME} ${UPDATED_SRC_FILES})
set_target_properties(app_${COMP_SRC_APP_NAME} PROPERTIES OUTPUT_NAME ${COMP_SRC_APP_NAME})
if(NOT "${UPDATED_LIB_DEPS}" STREQUAL "")
    target_link_libraries(app_${COMP_SRC_APP_NAME} PUBLIC ${UPDATED_LIB_DEPS})
endif()
BOZ_INSTALL_ITEM(app_${COMP_SRC_APP_NAME})
