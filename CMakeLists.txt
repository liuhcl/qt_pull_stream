cmake_minimum_required(VERSION 3.25)
project(pull_the_video_stream)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/0_MySoftware/Qt/5.12.9/mingw73_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Sql
        SerialPort
        Network
        REQUIRED)

message(${CMAKE_SOURCE_DIR})
# 指定 FFMPEG 头文件查找目录
#           CMAKE_SOURCE_DIR 指的是当前的文件地址
include_directories(${CMAKE_SOURCE_DIR}/ffmpeg/include ${CMAKE_SOURCE_DIR}/opencv/include)

# 指定引入的库文件所在路径
link_directories(${CMAKE_SOURCE_DIR}/ffmpeg/lib ${CMAKE_SOURCE_DIR}/opencv/lib)

add_executable(pull_the_video_stream main.cpp
                rtsp/rtsp.cpp rtsp/rtsp.h
                rtsp/rtspUI/rtspui.cpp rtsp/rtspUI/rtspui.h rtsp/rtspUI/rtspui.ui
                rtsp/addURL/addurl.cpp rtsp/addURL/addurl.h rtsp/addURL/addurl.ui
                rtsp/mysql/mysql.cpp rtsp/mysql/mysql.h
                rtsp/videoWin/videoLabel.cpp rtsp/videoWin/videoLabel.h
                rtsp/listNode/videoList.cpp rtsp/listNode/videoList.h
                rtsp/mySerialPort/mySerialPort.cpp rtsp/mySerialPort/mySerialPort.h
                rtsp/rtspUI/switchBtn/SwitchBtn.cpp rtsp/rtspUI/switchBtn/SwitchBtn.h
                rtsp/rtspUI/videoScrollArea/videoScrollArea.cpp rtsp/rtspUI/videoScrollArea/videoScrollArea.h
                rtsp/rtspUI/pushBtn/pushBtn.cpp rtsp/rtspUI/pushBtn/pushBtn.h
)

target_link_libraries(pull_the_video_stream
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::SerialPort
        Qt5::Network

        # 注意这些库的顺序必须按照如下进行 , 否则会报错
        #  这些库之间有依赖的关系 , 必须按照顺序加载库 , 如 avcodec 内部依赖 avformat 库
        avfilter
        avformat
        avcodec
        avutil
        swresample
        swscale

        #FFMPEG 使用到了 libz 库 , 没有会报错
        #   FFMPEG 对于 z 的依赖是以动态库的形式进行的
        #   如果 FFMPEG 是动态库 , 那么可以不链接这个库 , 可以运行时链接这个库
        #   当前 FFMPEG 是静态库 , 需要在编译时将这个库打包到静态库中
        #   推荐使用静态库 , 静态库打包出来的库比动态库小很多 , 一倍左右
        z

        #RTSP
        wsock32
        )

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets Sql SerialPort Network)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
