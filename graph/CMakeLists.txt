cmake_minimum_required(VERSION 3.10)
project(graph)

set(CMAKE_CXX_STANDARD 14)

add_executable(graph main.cpp)

include_directories(graph_lib)
add_subdirectory(graph_lib)
add_subdirectory(google_tests)
target_link_libraries(graph PRIVATE graph::graph_lib)

