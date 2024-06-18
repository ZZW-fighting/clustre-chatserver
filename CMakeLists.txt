cmake_minimum_required (VERSION 3.0) #要求cmake最低的版本号
project (chatserver) # 定义当前工程名字
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) #设置可执行文件最终存储的路径

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)


add_subdirectory(src)