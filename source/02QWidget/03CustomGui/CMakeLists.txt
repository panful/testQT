set(target_name "02_03_CustomGui")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS Widgets OpenGLWidgets REQUIRED)

set(CMAKE_AUTOUIC OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC OFF)

add_executable(${target_name} main.cpp widget.cpp widget.h)

target_link_libraries(${target_name}
    PRIVATE
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core
        Qt${SYSTEM_QT_MAJOR_VERSION}::Widgets
)
