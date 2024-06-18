cmake_minimum_required (VERSION 3.0) #要求cmake最低的版本号
project (chatserver) # 定义当前工程名字
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
add_executable(server muduo_server.cpp)
target_link_libraries(server muduo_net muduo_base pthread)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) #设置可执行文件最终存储的路径