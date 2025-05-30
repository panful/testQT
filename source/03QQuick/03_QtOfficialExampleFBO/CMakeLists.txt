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
    "03_03.qml"
)

target_link_libraries(${target_name}
    PRIVATE 
        Qt${SYSTEM_QT_MAJOR_VERSION}::Core
        Qt${SYSTEM_QT_MAJOR_VERSION}::Gui
        Qt${SYSTEM_QT_MAJOR_VERSION}::Qml
        Qt${SYSTEM_QT_MAJOR_VERSION}::Quick
)
