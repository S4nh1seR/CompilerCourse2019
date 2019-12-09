cmake_minimum_required (VERSION 3.10)
project(syntax_tree CXX)

include_directories(./visitors)
include_directories(./expression)
include_directories(./statements)


set(CMAKE_CXX_STANDARD 17)

add_library(irt_tree STATIC Exp.cpp)
