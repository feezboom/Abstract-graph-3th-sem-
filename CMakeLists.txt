cmake_minimum_required (VERSION 3.0)
project (ninja_turtles)

#set(CMAKE_VERBOSE_MAKEFILE on)
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
#message("cxx Flags: " ${CMAKE_CXX_FLAGS})

# включаем поддержку c++14
set(CMAKE_CXX_STANDARD 14)

# jsoncpp переопределяет OUTPUT_DIRECTORY поэтому включаем его вначале
add_subdirectory(jsoncpp)

# определяем куда будет попадать результат сборки
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/libraries)

# подпроект с реализацией графа
add_subdirectory(agraph)
add_subdirectory(Tasks/commonstr)
# добавляем директорию для поиска сгенерированного заголовочного файла
include_directories(${PROJECT_BINARY_DIR}/agraph)
include_directories(${PROJECT_BINARY_DIR}/Tasks/commonstr)
# определяем списки исходников
set(sources test.cpp catch_inc.cpp)
set(headers catch.hpp)

# добавляем путь для поиска библиотеки jsoncpp (т.к. OUTPUT_DIRECTORY для него другая)
link_directories(${PROJECT_BINARY_DIR}/jsoncpp/lib)

# создаем целевой проект
add_executable(tests ${sources} ${headers})
# указываем зависимости от дочерних проектов
add_dependencies(tests jsoncpp_lib agraph)
# указываем зависимости от библиотек
target_link_libraries(tests agraph jsoncpp)

target_link_libraries(tests commonstr_task_lib)
