cmake_minimum_required(VERSION 3.0)

project(2sat_task)

add_library(2sat SHARED 2sat.cpp)

add_executable(2sat_exe test.cpp 2sat.h)
#Connect library to executable file
target_link_libraries(2sat_exe 2sat)
