project(mini_java_compiler)
cmake_minimum_required(VERSION 3.10)

add_subdirectory(compiler)
add_subdirectory(syntaxtree)
add_subdirectory(visitor)
add_subdirectory(symbol_table)
add_subdirectory(irt)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
if (CMAKE_CXX_CPPCHECK)
    list(
            APPEND CMAKE_CXX_CPPCHECK
            "--enable=warning"
            "--inconclusive"
            "--force"
            "--inline-suppr"
    )
    execute_process (
            COMMAND ${CMAKE_CXX_CPPCHECK} --project=compile_commands.json
    )
endif()




