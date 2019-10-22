cmake_minimum_required (VERSION 3.10)
project(syntax_tree)

set(CMAKE_CXX_STANDARD 17)

add_library(syntax_tree STATIC Expressions.cpp Expressions.h SyntaxTreeNode.h Statements.h Statements.cpp)