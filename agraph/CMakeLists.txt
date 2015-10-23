cmake_minimum_required (VERSION 3.0)
project (agraph)


set(headers agraph.h)
set(sources agraph.cpp)

add_library(agraph SHARED ${sources} ${headers})

