cmake_minimum_required(VERSION 3.1)
project(transport)

set(CMAKE_CXX_STANDART 11)

set(HEADERS transport.h)
set(SOURCE_LIB transport.cpp)

link_directories(${PROJECT_BINARY_DIR}/agraph)

add_library(transport SHARED ${SOURCE_LIB})
add_executable(transport_local_test main.cpp)

target_link_libraries(transport_local_test transport graphs)
target_link_libraries(transport graphs)
