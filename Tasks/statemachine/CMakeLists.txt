cmake_minimum_required (VERSION 3.0)
project (statemachine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

add_library(statemachine_task_lib StateMachineGraph.cpp)

add_executable(statemachine_exe statemachineLocalTest.cpp  StateMachineGraph.h)
target_link_libraries(statemachine_exe statemachine_task_lib)
