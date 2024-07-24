
set(target_name "01_QtConsole")

find_package(Qt6 COMPONENTS REQUIRED Core Qml)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable (${target_name} "main.cpp" "mockQt.cpp" "mockQt.h" "test.qrc")

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Qml)
