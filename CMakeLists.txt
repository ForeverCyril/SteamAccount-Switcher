cmake_minimum_required(VERSION 3.15)
project(SteamAccountSwitcher VERSION 1.2.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(PROJECT_NAME ${PROJECT_NAME})
set(APP_NAME "Steam Account Switcher")
set(APP_VERSION ${PROJECT_VERSION})

find_package(Qt5 COMPONENTS LinguistTools Core Widgets REQUIRED)
find_program(LRELEASE_EXECUTABLE lrelease)

set(res_files res/res.qrc ${CMAKE_BINARY_DIR}/lang/lang.qrc)
set(ui_files src/mainwindow.ui)
file(GLOB_RECURSE src_files src/*.h src/*.cpp)

set(WINDOWS_RC  "application.rc")
configure_file(
    "${CMAKE_SOURCE_DIR}/${WINDOWS_RC}.in"
    "${CMAKE_BINARY_DIR}/${WINDOWS_RC}"
)

configure_file(
    "${CMAKE_SOURCE_DIR}/config.h.in"
    "${CMAKE_BINARY_DIR}/config.h"
)
configure_file(
        "${CMAKE_SOURCE_DIR}/lang/lang.qrc.in"
        "${CMAKE_BINARY_DIR}/lang/lang.qrc"
)
include_directories(${CMAKE_BINARY_DIR})

qt5_create_translation(ts_files
        ${CMAKE_SOURCE_DIR}/src lang/${PROJECT_NAME}_zh-CN.ts
        OPTIONS  -no-obsolete
)
set_source_files_properties(${ts_files} PROPERTIES OUTPUT_LOCATION "${CMAKE_BINARY_DIR}/lang")
qt5_add_translation(qm_files ${ts_files})

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_executable(SteamAccountSwitcher
        ${ts_files}
        ${qm_files}
        ${src_files}
        ${ui_files}
        ${res_files}
        ${CMAKE_BINARY_DIR}/${WINDOWS_RC}
    )
else()
    add_executable(SteamAccountSwitcher WIN32
        ${src_files}
        ${ui_files}
        ${res_files}
        ${ts_files}
        ${qm_files}
        ${CMAKE_BINARY_DIR}/${WINDOWS_RC}
    )
endif ()

target_link_libraries(SteamAccountSwitcher Qt5::Core Qt5::Widgets)

