    
set(LOCAL_BUILD_STATIC ON)
set(LOCAL_BUILD_SHARED OFF)
include(${BOZ_EXT_BUILD_DIR}/generic/update_lib_deps.cmake)

add_executable(test_${COMP_SRC_TEST_NAME} ${UPDATED_SRC_FILES})
# set_target_properties(test_${COMP_SRC_TEST_NAME} PROPERTIES OUTPUT_NAME ${COMP_SRC_TEST_NAME})
if(NOT "${UPDATED_LIB_DEPS}" STREQUAL "")
    target_link_libraries(test_${COMP_SRC_TEST_NAME} PUBLIC ${UPDATED_LIB_DEPS})
endif()

add_test(test_${COMP_SRC_TEST_NAME} test_${COMP_SRC_TEST_NAME})
