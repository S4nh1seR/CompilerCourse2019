project(mini_java_compiler)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -O1 -fno-omit-frame-pointer -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)

add_subdirectory(compiler)
add_subdirectory(syntaxtree)
add_subdirectory(visitor)
add_subdirectory(symbol_table)
#add_subdirectory(irt)

add_custom_target(
        cppcheck
        COMMAND cppcheck
        "--enable=all"
        "--std=c++11"
        "--inconclusive"
        "--force"
        "--inline-suppr"
        ${CMAKE_CURRENT_SOURCE_DIR}/compiler	
)
