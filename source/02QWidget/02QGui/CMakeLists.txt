set(target_name "02_02_QGui")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS REQUIRED Core Widgets)

set(CMAKE_AUTOMOC ON)  # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable (${target_name} "main.cpp")

target_link_libraries(${target_name}
    PRIVATE
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core
        Qt${SYSTEM_QT_MAJOR_VERSION}::Widgets
)
