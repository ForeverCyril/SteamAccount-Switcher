cmake_minimum_required(VERSION 3.15)
project(SteamAccountSwitcher VERSION 1.1.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS LinguistTools Core Widgets REQUIRED)
find_program(LRELEASE_EXECUTABLE lrelease)

aux_source_directory(src src)
set(res_files res/res.qrc)
set(ui_files src/mainwindow.ui)

set(MY_VERSIONINFO_RC "${CMAKE_SOURCE_DIR}/application.rc")
configure_file(${CMAKE_SOURCE_DIR}/application.rc.in
        "${MY_VERSIONINFO_RC}")

qt5_create_translation(QM_FILES ${src} ${ui_files} l18n/zh_CN.ts)
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_executable(SteamAccountSwitcher ${src} ${ui_files} ${res_files} l18n/zh_CN.ts ${MY_VERSIONINFO_RC})
else()
    add_executable(SteamAccountSwitcher WIN32 ${src} ${ui_files} ${res_files} l18n/zh_CN.ts ${MY_VERSIONINFO_RC})
endif ()

target_link_libraries(SteamAccountSwitcher Qt5::Core Qt5::Widgets)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/l18n")
execute_process(COMMAND  ${LRELEASE_EXECUTABLE} ${CMAKE_SOURCE_DIR}/l18n/zh_CN.ts -qm ${CMAKE_CURRENT_BINARY_DIR}/l18n/zh_CN.qm)
