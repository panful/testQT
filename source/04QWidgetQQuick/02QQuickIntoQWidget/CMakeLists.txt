set(target_name "04_02_QQuickIntoQWidget")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

add_executable (${target_name} "main.cpp")

target_link_libraries(${target_name}
    PRIVATE 
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core 
        Qt${SYSTEM_QT_MAJOR_VERSION}::Widgets
)
