set(target_name "02_06_QTranslate")

add_executable (${target_name} "main.cpp")

find_package(Qt6 COMPONENTS REQUIRED Core Widgets)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Widgets)
