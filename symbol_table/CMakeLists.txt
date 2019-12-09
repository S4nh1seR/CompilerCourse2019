cmake_minimum_required (VERSION 3.10)
project(symbol_table CXX)

set(syntaxtree_dir "../syntaxtree")
set(visitor_dir "../visitor")
include_directories(. ${syntaxtree_dir} ${visitor_dir})

set(CMAKE_CXX_STANDARD 17)

add_library(symbol_table STATIC SymbolTable.cpp MethodInfo.cpp ClassInfo.cpp)
