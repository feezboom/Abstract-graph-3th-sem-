cmake_minimum_required (VERSION 3.0)
include(GenerateExportHeader)

project (agraph)

set(headers agraph.h)
set(sources agraph.cpp)

# добавляем директорию для поиска сгенерированного заголовочного файла
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# создаем разделяемую библиотеку
add_library(agraph SHARED ${sources} ${headers})

# генерируем заголовочный файл с определениями для экспорта 
generate_export_header(agraph)
