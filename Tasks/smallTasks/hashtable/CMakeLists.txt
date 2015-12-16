cmake_minimum_required (VERSION 3.0)
project (hashtable)

set(CMAKE_CXX_STANDARD 14)

set(source_exe main.cpp)
set(headers hashtable.h hashtable.hpp)

add_executable(hashTest ${source_exe} ${headers})

