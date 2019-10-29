cmake_minimum_required (VERSION 3.10)

project(visitor)

set(graph_dir "../graph/graph_lib")
set(syntaxtree_dir "../syntaxtree")
include_directories(. ${graph_dir} ${syntaxtree_dir})

set(CMAKE_CXX_STANDARD 17)

add_library(visitor Visitor.h SerializeVisitor.h SerializeVisitor.cpp)
