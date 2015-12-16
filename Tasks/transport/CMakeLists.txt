cmake_minimum_required(VERSION 3.0)
project(transport)

set(CMAKE_CXX_STANDART 14)
add_definitions("-std=c++11")

add_library(transport_task_lib transport.cpp)

add_executable(transport_exe transportLocalTest.cpp)
target_link_libraries(transport_exe transport_task_lib)
