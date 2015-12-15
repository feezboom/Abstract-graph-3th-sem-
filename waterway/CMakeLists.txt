cmake_minimum_required(VERSION 3.2)
project(waterway)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_library(waterway_l FenwickTree.cpp WaterWayTesting.cpp)

set(SOURCE_FILES WaterTest.cpp FenwickTree.cpp FenwickTree.h WaterWayTesting.cpp WaterWayTesting.h)
add_executable(waterway ${SOURCE_FILES})

add_dependencies(waterway jsoncpp_lib)
