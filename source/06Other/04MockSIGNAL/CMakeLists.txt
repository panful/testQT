set(target_name "06_04_MockSIGNAL")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS REQUIRED Core )

set(CMAKE_AUTOMOC ON)  # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable (${target_name} "main.cpp")

target_link_libraries(${target_name} PRIVATE Qt${SYSTEM_QT_MAJOR_VERSION}::Core)
