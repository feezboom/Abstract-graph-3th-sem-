cmake_minimum_required (VERSION 3.0)
project (ninja_turtles)

ADD_DEFINITIONS("-g")

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

<<<<<<< HEAD
# jsoncpp ÔÂÂÓÔÂ‰ÂÎˇÂÚ OUTPUT_DIRECTORY ÔÓ˝ÚÓÏÛ ‚ÍÎ˛˜‡ÂÏ Â„Ó ‚Ì‡˜‡ÎÂ
add_subdirectory(jsoncpp)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
=======
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
>>>>>>> 758e14ce6611f25bed0f376a3d864e504bd388e4

#Where to search headers
include_directories(2sat)
include_directories(transport)
include_directories(salesman)
include_directories(smallTasks/hashtable)
include_directories(smallTasks/ukkonen)
include_directories(${PROJECT_BINARY_DIR}/agraph)

#Where to search and build independent subprojects
<<<<<<< HEAD
=======
add_subdirectory(agraph)
add_subdirectory(jsoncpp)
>>>>>>> 758e14ce6611f25bed0f376a3d864e504bd388e4
add_subdirectory(2sat)
add_subdirectory(transport)
add_subdirectory(salesman)
add_subdirectory(smallTasks/hashtable)
add_subdirectory(smallTasks/ukkonen)

set(sources main_test.cpp catch_inc.cpp)
set(headers catch.hpp)

#include_directories("${CMAKE_SOURCE_DIR}/jsoncpp/include" "${CMAKE_SOURCE_DIR}/agraph")
link_directories("${CMAKE_BINARY_DIR}/jsoncpp/lib")

add_executable(tests ${sources} ${headers})
#–ü–æ—Ä—è–¥–æ–∫ —Å–±–æ—Ä–∫–∏
add_dependencies(tests jsoncpp_lib 2sat graphs transport salesman)
#–Ø–∑—ã–∫–æ–≤—ã–µ –∑–∞–≤–∏—Å–∏–º–æ—Å—Ç–∏
target_link_libraries(tests jsoncpp 2sat graphs transport)
