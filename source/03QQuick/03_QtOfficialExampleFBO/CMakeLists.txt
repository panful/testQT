set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(target_name "03_03_QtOfficialExampleFBO")

find_package(Qt6 COMPONENTS Core Gui Qml Quick)

add_executable (${target_name} "main.cpp" "logorenderer.h" "logorenderer.cpp" "fboinsgrenderer.h" "fboinsgrenderer.cpp" "03_03.qml")

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)
