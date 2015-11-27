cmake_minimum_required (VERSION 3.0)
include(GenerateExportHeader)

project (agraph)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

# добавляем директорию для поиска сгенерированного заголовочного файла
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# создаем разделяемую библиотеку
set(sources agraph.cpp LandingGraph.cpp SalesmanGraph.cpp)
set(headers TransportGraph.h TransportGraph.h LandingGraph.h SalesmanGraph.h)
add_library(graphs SHARED ${sources})

add_executable(agraph_test test.cpp ${headers})

target_link_libraries(agraph_test graphs)

# генерируем заголовочный файл с определениями для экспорта 
generate_export_header(graphs)
