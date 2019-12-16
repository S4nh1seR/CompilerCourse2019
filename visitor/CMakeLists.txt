cmake_minimum_required (VERSION 3.10)

project(visitor)

set(irt_dir "../irt")
set(graph_dir "../graph/graph_lib")
set(syntaxtree_dir "../syntaxtree")
set(symbol_table_dir "../symbol_table")

include_directories(. ${graph_dir} ${syntaxtree_dir} ${symbol_table_dir} ${irt_dir})

set(CMAKE_CXX_STANDARD 17)

add_library(visitor SerializeVisitor.cpp BuildSymbolTableVisitor.cpp TypeCheckerVisitor.cpp IrTreeBuilder.cpp IrtWrappers.cpp IrtSerializeVisitor.cpp)
