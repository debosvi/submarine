
set(LOCAL_APP echo_terminal)

set(LOCAL_SOURCES 
    main.c
)


include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${LOCAL_APP}
    ${LOCAL_SOURCES}
)

target_link_libraries(${LOCAL_APP} 
    skarnet
)

