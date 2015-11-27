cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

project(salesman)

#add_subdirectory(jsoncpp)
link_directories("${CMAKE_BINARY_DIR}/jsoncpp/lib")

add_library(salesman SHARED salesman.cpp)
add_executable(salesmanTest main.cpp salesman.h)

#Link library to executable file
target_link_libraries(salesmanTest salesman)
target_link_libraries(salesmanTest jsoncpp)
target_link_libraries(salesman graphs)
