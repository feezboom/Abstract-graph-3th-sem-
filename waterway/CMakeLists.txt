cmake_minimum_required(VERSION 3.3)
project(waterway)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES WaterWayTest.cpp)
add_executable(waterway ${SOURCE_FILES})