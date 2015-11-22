cmake_minimum_required (VERSION 3.0)
include(GenerateExportHeader)

project (agraph)

set(headers agraph.h graphs.h)
set(sources agraph.cpp graphs.cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# добавляем директорию для поиска сгенерированного заголовочного файла
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# создаем разделяемую библиотеку
add_library(agraph SHARED ${sources} ${headers})
add_executable(agraph_test test.cpp agraph)

# генерируем заголовочный файл с определениями для экспорта 
generate_export_header(agraph)
