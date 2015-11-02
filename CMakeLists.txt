cmake_minimum_required (VERSION 3.0)
project (ninja_turtles)

ADD_DEFINITIONS("-std=c++11")

#set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

include_directories(2sat)

add_subdirectory(jsoncpp)
add_subdirectory(agraph)
add_subdirectory(2sat)
add_subdirectory(Graph)

set(sources test.cpp catch_inc.cpp)
set(headers catch.hpp)

#include_directories("${CMAKE_SOURCE_DIR}/jsoncpp/include" "${CMAKE_SOURCE_DIR}/agraph")
link_directories("${CMAKE_BINARY_DIR}/jsoncpp/lib")

add_executable(tests ${sources} ${headers})
add_dependencies(tests jsoncpp_lib agraph)
target_link_libraries(tests jsoncpp agraph)
