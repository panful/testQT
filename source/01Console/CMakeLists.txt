cmake_minimum_required (VERSION 3.8)

set(target_name "01_QtConsole")

find_package(Qt6 COMPONENTS REQUIRED Core Core5Compat Qml)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable (${target_name} "main.cpp" "mockQt.cpp" "mockQt.h" "resources/test.qrc")

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Core5Compat Qt6::Qml)

install(TARGETS ${target_name}
        RUNTIME DESTINATION ./
)