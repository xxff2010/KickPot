cmake_minimum_required(VERSION 3.21)
project(KickPot VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(KickPot WIN32
    main.cpp
    mainwindow.h
    mainwindow.cpp
    resources.qrc
    core/appmanager.h
    core/appmanager.cpp
    core/pages.h
    ui/statcard.h
    ui/navbutton.h
    ui/dashboard.h
    ui/dashboard.cpp
    ui/placeholderpage.h
    ui/placeholderpage.cpp
    ui/settingspage.h
    ui/settingspage.cpp
)

# Allows includes such as "core/appmanager.h" from any file.
target_include_directories(KickPot PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(KickPot PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

if(MSVC)
    # /utf-8 is required so Arabic text in source files compiles correctly.
    target_compile_options(KickPot PRIVATE /utf-8 /W4)
endif()

# Copy the Qt DLLs next to the exe so the app runs directly from Visual Studio.
if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt
                 HINTS "${Qt6_DIR}/../../../bin")
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET KickPot POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" --no-translations "$<TARGET_FILE:KickPot>"
            COMMENT "Deploying Qt runtime files with windeployqt")
    else()
        message(WARNING "windeployqt not found. The app may fail to start because Qt DLLs are missing.")
    endif()
endif()
