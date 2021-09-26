cmake_minimum_required(VERSION 3.4.1)

# 外部头文件路径，因为我们要引用 libyuv.h
include_directories(libyuv/include)

# 添加子项目，libyuv 作为一个子项目自己编译，有自己的 CMakeList.txt。
# 编译结果存放在 build 目录下，可以在里面找到生成的 .so 文件。
add_subdirectory(libyuv ./build)

# 生成动态链接库 yuvutil,  YuvJni.cpp 是我们的源代码，可以指定多个源文件。
add_library(yuvlib SHARED
        YuvConvert.cpp
        YuvConvert.h
        YuvJni.cpp
        YuvJni.h)

# 添加NDK里面 编译好的  log 库
find_library(log-lib
        log)

# 把 yuv (这个是 libyuv 子项目生成的 yuv.so) 和 log 库链接到 yuvutil 中
target_link_libraries(yuvlib
        ${log-lib}
        jnigraphics
        yuv)
