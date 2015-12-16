cmake_minimum_required(VERSION 3.2)
project(waterway)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_library(waterway_task_lib FenwickTree.cpp)

add_executable(waterway_exe waterwayLocalTest.cpp)
target_link_libraries(waterway_exe waterway_task_lib)