cmake_minimum_required(VERSION 3.8)

set(target_name "06_01_01_PlayVideo")

find_package(Qt6 COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)  # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC ON)  # User Interface Compiler

add_executable(${target_name} "main.cpp" "widget.h" "widget.cpp")

target_include_directories(${target_name} PRIVATE ../../../../3rdparty/FFMPEG/include)

target_link_directories(${target_name} PRIVATE ../../../../3rdparty/FFMPEG/lib)
target_link_libraries(${target_name} PRIVATE Qt6::Widgets avcodec avformat avfilter avutil swscale)

install(TARGETS ${target_name} RUNTIME DESTINATION ./)
