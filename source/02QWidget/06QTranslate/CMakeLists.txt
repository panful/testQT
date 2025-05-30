set(target_name "02_06_QTranslate")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS REQUIRED Core Widgets)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable (${target_name} "main.cpp" "MainWindow.h" "MainWindow.cpp" "translation.qrc")

target_link_libraries(${target_name}
    PRIVATE
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core
        Qt${SYSTEM_QT_MAJOR_VERSION}::Widgets
)
