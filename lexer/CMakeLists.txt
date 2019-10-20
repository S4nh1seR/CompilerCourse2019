cmake_minimum_required(VERSION 3.10)
project(Lexer)

set(CMAKE_CXX_STANDARD 14)

find_package(FLEX REQUIRED)

flex_target(flex_scanner scanner.ll ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)

# Сгенерированный файл записывается в переменную FLEX_flex_scanner_OUTPUTS, 
# можем использовать её, как исходный файл
add_library(myscanner ${FLEX_flex_scanner_OUTPUTS})

add_executable(main main.cpp)

target_link_libraries(main myscanner)	

