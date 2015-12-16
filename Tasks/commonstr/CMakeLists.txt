cmake_minimum_required(VERSION 3.0)
project(commonStr)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(commonstr_task_lib LongestCommonSubstring.cpp)

add_executable(commonstr_exe commonstrLocalTest.cpp LongestCommonSubstring.h)

target_link_libraries(commonstr_exe commonstr_task_lib)