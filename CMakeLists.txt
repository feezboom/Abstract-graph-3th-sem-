cmake_minimum_required (VERSION 3.0)
project (mipt)

#set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")

set(CMAKE_CXX_STANDARD 11)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

add_subdirectory(jsoncpp)
add_subdirectory(agraph)

set(sources test.cpp catch_inc.cpp)
set(headers catch.hpp)

#include_directories("${CMAKE_SOURCE_DIR}/jsoncpp/include" "${CMAKE_SOURCE_DIR}/agraph")
link_directories("${CMAKE_BINARY_DIR}/jsoncpp/lib")

add_executable(tests ${sources} ${headers})
add_dependencies(tests jsoncpp_lib agraph)
target_link_libraries(tests jsoncpp agraph)
