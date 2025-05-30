set(target_name "03_01_WindowButton")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS Core Gui Quick Qml REQUIRED)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable (${target_name} "main.cpp")

target_link_libraries(${target_name}
    PRIVATE 
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core
        Qt${SYSTEM_QT_MAJOR_VERSION}::Gui
        Qt${SYSTEM_QT_MAJOR_VERSION}::Qml
        Qt${SYSTEM_QT_MAJOR_VERSION}::Quick
)

# 将 qml 文件拷贝到可执行文件目录
add_custom_command(TARGET ${target_name}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/03_01.qml"
        "$<TARGET_FILE_DIR:${target_name}>/03_01.qml"
)
