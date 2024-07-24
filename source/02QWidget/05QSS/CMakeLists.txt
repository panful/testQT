cmake_minimum_required (VERSION 3.8)

set(target_name "02_05_QSS")

add_executable (${target_name} "main.cpp")

find_package(Qt6 COMPONENTS REQUIRED Core Widgets)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Widgets)

install(TARGETS ${target_name}
        RUNTIME DESTINATION ./
)