cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

project(2sat)

add_library(2sat_task_lib 2sat.cpp)

add_executable(2sat_exe 2satLocalTest.cpp 2sat.h)
target_link_libraries(2sat_exe 2sat_task_lib)

