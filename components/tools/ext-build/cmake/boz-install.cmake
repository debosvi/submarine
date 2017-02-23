
macro(BOZ_INSTALL_HEADER arg)
	get_filename_component(prefix ${arg} DIRECTORY )
	get_filename_component(name ${arg} NAME )
	message(STATUS "Install header: ${name}")
	install(FILES ${GENERATED_INCLUDE_DIR}/public/${arg}
		DESTINATION ${HEADER_INSTALL_DIR}/${prefix}
		)
endmacro()

macro(BOZ_INSTALL_ITEM target)
    message(STATUS "Install target ${target}")
    install(TARGETS ${target}
        RUNTIME DESTINATION ${BINARY_INSTALL_DIR}
        LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIBRARY_INSTALL_DIR}/static
    )
endmacro()

# uninstall target
configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/boz-uninstall.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)