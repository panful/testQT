
set(target_name "03_02_QmlCallCxx")

add_executable (${target_name} "main.cpp" "QDataMgr.h" "QDataMgr.cpp" "03_02.qml") # 可以在target_sources中包含qml文件

find_package(Qt6 COMPONENTS Core Gui Quick Qml  REQUIRED)

set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC ON) # Resource Compiler
set(CMAKE_AUTOUIC ON) # User Interface Compiler

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)

#target_sources(${target_name} PRIVATE 03_02.qml)
