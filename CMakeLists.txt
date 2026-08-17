cmake_minimum_required(VERSION 3.16)

project(QtCalc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(QtCalc
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
    ${CMAKE_CURRENT_SOURCE_DIR}/logo.rc
)

target_link_libraries(QtCalc PRIVATE Qt6::Widgets)

# Installation

include(GNUInstallDirs)

install(TARGETS QtCalc
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/icon/logo.png
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps
    RENAME qtcalc.png
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/qtcalc.desktop.in
    ${CMAKE_CURRENT_BINARY_DIR}/qtcalc.desktop
    @ONLY
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/qtcalc.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)