cmake_minimum_required (VERSION 3.0)
project (safeConstructor)

ADD_DEFINITIONS("-std=c++11")

set(source_exe main.cpp)
set(headers safe.h)

add_executable(safeTest ${source_exe} ${headers})
