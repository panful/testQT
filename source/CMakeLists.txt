cmake_minimum_required(VERSION 3.12)

add_subdirectory("01Console")
add_subdirectory("02QWidget")
add_subdirectory("03QQuick")
add_subdirectory("04QWidgetQQuick")
add_subdirectory("05QSocket")
add_subdirectory("06Other")

install(DIRECTORY resource DESTINATION .)
