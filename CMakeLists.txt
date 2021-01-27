cmake_minimum_required(VERSION 3.1.0)

project(yellow-tomoto VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(run
    tomato.ui
    Dialog.cpp
    TomatoState.cpp
    main.cpp
    analogclock.cpp
    tomato.qrc
)

target_link_libraries(run Qt::Widgets Qt::Network)
