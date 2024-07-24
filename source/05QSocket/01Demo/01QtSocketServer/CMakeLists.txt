cmake_minimum_required(VERSION 3.8)

set(target_name "05_01_01_TcpServer")

find_package(Qt6 COMPONENTS Core Widgets Network)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

add_executable(${target_name} "main.cpp" "widget.cpp" "widget.h")

target_link_libraries(${target_name} PRIVATE Qt6::Widgets Qt6::Network)

install(TARGETS ${target_name}
        RUNTIME DESTINATION ./
)
