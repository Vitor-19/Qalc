cmake_minimum_required(VERSION 3.16)

project(Qalc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(Qalc
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
    ${CMAKE_CURRENT_SOURCE_DIR}/logo.rc
)

target_link_libraries(Qalc PRIVATE Qt6::Widgets)

# Installation

include(GNUInstallDirs)

install(TARGETS Qalc
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/icon/logo.png
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps
    RENAME qalc.png
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/qalc.desktop.in
    ${CMAKE_CURRENT_BINARY_DIR}/qalc.desktop
    @ONLY
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/qalc.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)