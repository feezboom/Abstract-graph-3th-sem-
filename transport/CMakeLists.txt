cmake_minimum_required(VERSION 3.2.2)

project(transport)

set(HEADERS transport.h)
set(SOURCE_LIB transport.cpp)

add_library(TRANSPORT SHARED ${SOURCE_LIB})

add_executable(transport_local_test main.cpp ${HEADERS})
target_link_libraries(transport_local_test TRANSPORT)
