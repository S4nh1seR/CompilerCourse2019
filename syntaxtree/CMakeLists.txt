cmake_minimum_required (VERSION 3.10)
project(syntax_tree CXX)

include_directories(../visitor)

set(CMAKE_CXX_STANDARD 17)

add_library(syntax_tree STATIC Expressions.cpp Statements.cpp Declarations.cpp MainClass.cpp Goal.cpp)
