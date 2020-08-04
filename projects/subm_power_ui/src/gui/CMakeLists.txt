
set(LOCAL_APP console_terminal)

set(LOCAL_SOURCES 
    mainwindow.cpp 
    console.cpp
    settingsdialog.cpp
    main.cpp
)

qt5_wrap_ui(LOCAL_SOURCES_UI
    settingsdialog.ui
    mainwindow.ui
)

qt5_wrap_cpp(LOCAL_SOURCES_MOC 
    mainwindow.h
    console.h
    settingsdialog.h
    )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(${LOCAL_APP}
    ${LOCAL_SOURCES_UI}
    ${LOCAL_SOURCES_MOC}
    ${LOCAL_SOURCES}
)

target_link_libraries(${LOCAL_APP} 
    Qt5::SerialPort
    Qt5::Widgets
    )

