project(mini_java_compiler)
cmake_minimum_required(VERSION 3.10)

add_subdirectory(compiler)
add_subdirectory(syntaxtree)
add_subdirectory(visitor)
add_subdirectory(symbol_table)
add_subdirectory(irt)