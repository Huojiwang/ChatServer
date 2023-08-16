cmake_minimum_required(VERSION 3.16)
project(muduo_server)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g ) #-O2

#配置库文件搜索路径

#设置可执行文件存储的命令
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#link_directories()


#配置头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

#加载子目录
add_subdirectory (src)

