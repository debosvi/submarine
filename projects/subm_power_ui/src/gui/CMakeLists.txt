
set(LOCAL_APP console_terminal)

set(LOCAL_SOURCES 
    mainwindow.cpp 
    console.cpp
    main.cpp
)

qt5_wrap_ui(LOCAL_SOURCES_UI
    mainwindow.ui
)

qt5_wrap_cpp(LOCAL_SOURCES_MOC 
    mainwindow.h
    console.h
    )
	
qt5_add_resources(LOCAL_SOURCES_QRC terminal.qrc)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${LOCAL_APP}
    ${LOCAL_SOURCES_QRC}
    ${LOCAL_SOURCES_UI}
    ${LOCAL_SOURCES_MOC}
    ${LOCAL_SOURCES}
)

target_link_libraries(${LOCAL_APP} 
    Qt5::Widgets
    )

