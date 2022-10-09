cmake_minimum_required(VERSION 3.8)

add_subdirectory("01PlayVideo")

# 拷贝ffmpeg动态库文件到安装目录
FILE(GLOB DLL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../../3rdparty/FFMPEG/bin/*.dll)
install(FILES ${DLL_FILES} DESTINATION .)