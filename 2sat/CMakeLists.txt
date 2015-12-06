cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

project(2sat_task)

#add_subdirectory(jsoncpp)
link_directories("${CMAKE_BINARY_DIR}/jsoncpp/lib")

add_library(2sat 2sat.cpp)
add_executable(2sat_exe test.cpp 2sat.h)

#Link library to executable file
target_link_libraries(2sat_exe 2sat)
target_link_libraries(2sat_exe jsoncpp)
target_link_libraries(2sat jsoncpp)
