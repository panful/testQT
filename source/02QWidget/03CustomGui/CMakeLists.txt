cmake_minimum_required(VERSION 3.5)

set(target_name "02_03_CustomGui")

#set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
#set(CMAKE_INCLUDE_CURRENT_DIR ON) # 自动添加CMAKE_CURRENT_BINARY_DIR和CMAKE_CURRENT_SOURCE_DIR到当前处理的CMakeLists.txt

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

install(TARGETS ${target_name}
        RUNTIME DESTINATION ./
)
