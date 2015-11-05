cmake_minimum_required (VERSION 3.0)
project (hashtable)

ADD_DEFINITIONS("-std=c++11")

set(source_exe main.cpp)
set(headers hashtable.h hashtable.hpp)

add_executable(hashTest ${source_exe} ${headers})

