cmake_minimum_required (VERSION 3.8)

set(target_name "03_01_WindowButton")

add_executable (${target_name} "main.cpp" "03_01.qml") # 可以在target_sources中包含qml文件

find_package(Qt6 COMPONENTS Core Gui Quick Qml  REQUIRED)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)

install(TARGETS ${target_name} RUNTIME DESTINATION .)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/03_01.qml DESTINATION .)

#target_sources(${target_name} PRIVATE 03_01.qml)
