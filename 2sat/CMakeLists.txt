cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

project(2sat_task)

add_subdirectory(jsoncpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

link_directories("../${CMAKE_BINARY_DIR}/jsoncpp/lib")

set(headers 2sat.h)
set(sources 2sat.cpp jsoncpp)

add_library(2sat SHARED ${sources} ${headers})
add_executable(2satLittleLocalTest test.cpp 2sat jsoncpp)

#Link library to executable file
add_dependencies(2satLittleLocalTest 2sat)
target_link_libraries(2satLittleLocalTest 2sat jsoncpp)
