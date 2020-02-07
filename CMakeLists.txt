cmake_minimum_required(VERSION 3.15)
project(SteamAccountSwitcher VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS LinguistTools Core Widgets REQUIRED)

aux_source_directory(src src)
set(res_files res/res.qrc)
set(ui_files)
set(TS_FILES l10n/zh_CN.ts)

set(MY_VERSIONINFO_RC "${CMAKE_SOURCE_DIR}/application.rc")
configure_file(${CMAKE_SOURCE_DIR}/application.rc.in
        "${MY_VERSIONINFO_RC}")


add_executable(SteamAccountSwitcher WIN32 ${src} ${ui_files} ${res_files} ${MY_VERSIONINFO_RC})
target_link_libraries(SteamAccountSwitcher Qt5::Core Qt5::Widgets)