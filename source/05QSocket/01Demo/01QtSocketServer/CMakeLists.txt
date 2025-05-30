set(target_name "05_01_01_TcpServer")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS Core Widgets Network)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable(${target_name} "main.cpp" "widget.cpp" "widget.h")

target_link_libraries(${target_name}
    PRIVATE
        Qt${SYSTEM_QT_MAJOR_VERSION}::Widgets 
        Qt${SYSTEM_QT_MAJOR_VERSION}::Network
)
