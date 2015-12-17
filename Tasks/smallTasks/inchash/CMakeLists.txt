cmake_minimum_required(VERSION 3.0)
project(inchash)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(inchash_task_lib inchash.cpp)
add_executable(inchash_exe inchashLocalTest.cpp inchash.h)
target_link_libraries(inchash_exe inchash_task_lib)

