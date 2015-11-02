cmake_minimum_required(VERSION 3.1)
project(graph_class)

set(CMAKE_CXX_STANDART 11)
ADD_DEFINITIONS("-std=c++11")

set(LIB graph.cpp)
set(SOURCES main.cpp)
set(HEADERS graph.h)


add_executable(graph_local_tests ${SOURCES} ${HEADERS})

