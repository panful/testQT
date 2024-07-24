
set(target_name "02_03_CustomGui")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets OpenGLWidgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
)

add_executable(${target_name} ${PROJECT_SOURCES})

target_link_libraries(${target_name} PRIVATE Qt6::Widgets Qt6::OpenGLWidgets)
