set(target_name "04_01_QWidgetIntoQQuick")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS Core Gui Quick Qml Widgets QuickWidgets REQUIRED)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable (${target_name} "main.cpp" "qmlWidget.h" "qmlWidget.cpp")

target_link_libraries(${target_name}
    PRIVATE
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core
        Qt${SYSTEM_QT_MAJOR_VERSION}::Gui
        Qt${SYSTEM_QT_MAJOR_VERSION}::Qml
        Qt${SYSTEM_QT_MAJOR_VERSION}::Quick
        Qt${SYSTEM_QT_MAJOR_VERSION}::Widgets
        Qt${SYSTEM_QT_MAJOR_VERSION}::QuickWidgets
)

target_sources(${target_name} PRIVATE main.qml)
