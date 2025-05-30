set(target_name "03_03_QtOfficialExampleFBO")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS Core Gui Qml Quick)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

add_executable (${target_name} 
    "main.cpp" 
    "logorenderer.h" 
    "logorenderer.cpp" 
    "fboinsgrenderer.h" 
    "fboinsgrenderer.cpp" 
)

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
        "${CMAKE_CURRENT_SOURCE_DIR}/03_03.qml"
        "$<TARGET_FILE_DIR:${target_name}>/03_03.qml"
)
