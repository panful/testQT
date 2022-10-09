cmake_minimum_required (VERSION 3.8)

set(target_name "04_01_QWidgetIntoQQuick")

add_executable (${target_name} "main.cpp" "qmlWidget.h" "qmlWidget.cpp")

find_package(Qt6 COMPONENTS Core Gui Quick Qml Widgets QuickWidgets REQUIRED)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Widgets Qt6::QuickWidgets)

install(TARGETS ${target_name}
        RUNTIME DESTINATION ./
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/main.qml DESTINATION ./)

target_sources(${target_name} PRIVATE main.qml)