cmake_minimum_required(VERSION 3.18)

project(Cyclone)
set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR src)
file(GLOB CYCLONE_SRC "${SRC_DIR}/*.h" "${SRC_DIR}/*.cpp")


add_library(Cyclone STATIC ${CYCLONE_SRC})
target_include_directories(Cyclone INTERFACE ${SRC_DIR})
