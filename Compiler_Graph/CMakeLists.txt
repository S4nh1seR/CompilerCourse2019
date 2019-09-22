cmake_minimum_required(VERSION 3.10)
project(Compiler_Graph)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler_Graph main.cpp)

include_directories(graph_lib)
add_subdirectory(graph_lib)
add_subdirectory(google_tests)
target_link_libraries(Compiler_Graph PRIVATE Compiler_Graph::graph_lib)

