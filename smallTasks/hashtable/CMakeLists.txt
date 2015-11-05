cmake_minimum_required (VERSION 3.0)
project (hashtable)

ADD_DEFINITIONS("-std=c++11")

set(source_exe main.cpp)
set(source_lib hashtable.cpp)
set(headers hashtable.h)

add_library(hashtable_lib ${source_lib})

add_executable(hashTest ${source_exe} ${headers})

target_link_libraries(hashTest hashtable_lib)
