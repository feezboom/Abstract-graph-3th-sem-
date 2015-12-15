cmake_minimum_required (VERSION 3.0)
project (ninja_turtles)

ADD_DEFINITIONS("-g")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# jsoncpp переопределяет OUTPUT_DIRECTORY поэтому включаем его вначале
add_subdirectory(jsoncpp)
# определяем куда будет попадать результат сборки
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# подпроект с реализацией графа
add_subdirectory(agraph)
add_subdirectory(2sat)
add_subdirectory(transport)
add_subdirectory(salesman)
add_subdirectory(waterway)
add_subdirectory(smallTasks/hashtable)

# добавляем директорию для поиска сгенерированного заголовочного файла
include_directories(${PROJECT_BINARY_DIR}/agraph)
include_directories(2sat)
include_directories(transport)
include_directories(salesman)
include_directories(waterway)
include_directories(smallTasks/hashtable)

# определяем списки исходников
set(sources main_test.cpp catch_inc.cpp)
set(headers catch.hpp)

# добавляем путь для поиска библиотеки jsoncpp (т.к. OUTPUT_DIRECTORY для него другая)
include_directories("${CMAKE_SOURCE_DIR}/jsoncpp/include" "${CMAKE_SOURCE_DIR}/agraph")
link_directories("${CMAKE_BINARY_DIR}/jsoncpp/lib")

# создаем целевой проект
add_executable(tests ${sources} ${headers})
# указываем зависимости от дочерних проектов
add_dependencies(tests jsoncpp_lib 2sat graphs transport salesman)
# указываем зависимости от библиотек
target_link_libraries(tests jsoncpp 2sat graphs transport waterway_l)
