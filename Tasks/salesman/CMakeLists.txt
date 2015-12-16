cmake_minimum_required(VERSION 3.2)
project(salesman)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp SalesmanGraph.cpp SalesmanGraph.h)
add_executable(salesman ${SOURCE_FILES})
