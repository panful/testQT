set(CMAKE_AUTOMOC ON) # Meta-Object Compiler
set(CMAKE_AUTORCC OFF) # Resource Compiler
set(CMAKE_AUTOUIC OFF) # User Interface Compiler

set(target_name "06_03_02_01_QmlEngine")

set(SRCS 
    "QFboItem.cpp"
    "FboRenderer.cpp"
)

set(HEADERS
    "QFboItem.h"
    "FboRenderer.h"
)

set(RSCS
    "01_03_02_01.qml"
)

add_executable (${target_name} main.cpp ${SRCS} ${HEADERS} ${RSCS})

find_package(Qt${SYSTEM_QT_MAJOR_VERSION} COMPONENTS Core Gui Quick Qml  REQUIRED)

target_link_libraries(${target_name} PRIVATE Qt${SYSTEM_QT_MAJOR_VERSION}::Core Qt${SYSTEM_QT_MAJOR_VERSION}::Gui Qt${SYSTEM_QT_MAJOR_VERSION}::Qml Qt${SYSTEM_QT_MAJOR_VERSION}::Quick)
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
