cmake_minimum_required (VERSION 3.10)
project(syntax_tree CXX)

include_directories(../syntaxtree)
include_directories(../visitor)

set(CMAKE_CXX_STANDARD 17)

add_library(irt_tree STATIC IrtExpressions.cpp IrtStatements.cpp)