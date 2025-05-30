
set(target_name "03_02_QmlCallCxx")

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS Core Gui Quick Qml  REQUIRED)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

add_executable (${target_name} "main.cpp" "QDataMgr.h" "QDataMgr.cpp" "03_02.qml") # 可以在target_sources中包含qml文件

target_link_libraries(${target_name}
    PRIVATE 
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core
        Qt${SYSTEM_QT_MAJOR_VERSION}::Gui
        Qt${SYSTEM_QT_MAJOR_VERSION}::Qml
        Qt${SYSTEM_QT_MAJOR_VERSION}::Quick
)

# target_sources(${target_name} PRIVATE 03_02.qml)
