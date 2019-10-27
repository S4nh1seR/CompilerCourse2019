project(simple_wc_example CXX)

cmake_minimum_required(VERSION 3.1)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(mc_parser
             parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/mc_parser.tab.cc)
FLEX_TARGET(mc_lexer
            scanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/mc_lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(mc_lexer mc_parser)

add_executable(my_wc
    main_parser.cpp

    ${FLEX_mc_lexer_OUTPUTS}
    ${BISON_mc_parser_OUTPUTS}
)
target_include_directories(my_wc
    PRIVATE
        .
        ${CMAKE_CURRENT_BINARY_DIR})
set_property(TARGET my_wc
             PROPERTY CXX_STANDARD 14)


