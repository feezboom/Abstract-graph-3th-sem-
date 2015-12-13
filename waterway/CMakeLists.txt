cmake_minimum_required(VERSION 3.3)
project(waterway)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCE_FILES WaterWayTest.cpp FenwickTree.cpp FenwickTree.h)
add_executable(waterway ${SOURCE_FILES})