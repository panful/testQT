set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(target_name "06_03_02_03_OfficialExample")

find_package(Qt6 COMPONENTS Core Gui Qml Quick)

add_executable (${target_name} "main.cpp" "logorenderer.h" "logorenderer.cpp" "fboinsgrenderer.h" "fboinsgrenderer.cpp" "01_03_02_03.qml")

target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick)
