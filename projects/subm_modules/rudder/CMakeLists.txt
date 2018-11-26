
set(COMP_NAME rudder)

add_executable(${COMP_NAME}
    main.c
)

target_link_libraries(${COMP_NAME}
    lib_s6cb_candev_shared
)

