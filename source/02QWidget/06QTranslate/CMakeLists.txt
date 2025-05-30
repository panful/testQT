set(target_name "02_06_QTranslate")

add_executable (${target_name} "main.cpp")

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS REQUIRED Core Widgets)

target_link_libraries(${target_name}
    PRIVATE
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core
        Qt${SYSTEM_QT_MAJOR_VERSION}::Widgets
)
