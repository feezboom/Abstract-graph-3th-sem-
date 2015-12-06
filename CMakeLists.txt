cmake_minimum_required (VERSION 3.0)
project (ninja_turtles)

ADD_DEFINITIONS("-g")

#set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

#Where to search headers
include_directories(2sat)
include_directories(transport)
include_directories(salesman)
include_directories(smallTasks/hashtable)
include_directories(smallTasks/ukkonen)
include_directories(${PROJECT_BINARY_DIR}/agraph)

#Where to search and build independent subprojects
add_subdirectory(agraph)
add_subdirectory(jsoncpp)
add_subdirectory(2sat)
add_subdirectory(transport)
add_subdirectory(salesman)
add_subdirectory(smallTasks/hashtable)
add_subdirectory(smallTasks/ukkonen)

set(sources main_test.cpp catch_inc.cpp)
set(headers catch.hpp)

include_directories("${CMAKE_SOURCE_DIR}/jsoncpp/include" "${CMAKE_SOURCE_DIR}/agraph")
link_directories("${CMAKE_BINARY_DIR}/jsoncpp/lib")

add_executable(tests ${sources} ${headers})
add_dependencies(tests jsoncpp_lib 2sat graphs transport salesman)
target_link_libraries(tests jsoncpp 2sat graphs transport)
