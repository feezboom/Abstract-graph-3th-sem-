cmake_minimum_required(VERSION 3.1)
project(transport)

set(CMAKE_CXX_STANDART 11)

set(HEADERS transport.h)
set(SOURCE_LIB transport.cpp)

add_library(TRANSPORT SHARED ${SOURCE_LIB})
add_executable(transport_local_test main.cpp ${HEADERS})
target_link_libraries(transport_local_test TRANSPORT)
