cmake_minimum_required (VERSION 3.8)

set(target_name "04_02_QQuickIntoQWidget")

add_executable (${target_name} "main.cpp")

find_package(Qt6 COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Widgets)

install(TARGETS ${target_name}
        RUNTIME DESTINATION ./
)