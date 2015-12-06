cmake_minimum_required (VERSION 3.0)
project (statemachine)

link_directories("${CMAKE_BINARY_DIR}/jsoncpp/lib")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_executable(stateMachine main.cpp StateMachineGraph.cpp StateMachineGraph.h)
