project(compiler CXX)

cmake_minimum_required(VERSION 3.10)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(parser
             parser.yy
             ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
FLEX_TARGET(lexer
            scanner.ll
            ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

set(SYNTAX_TREE_SRCS ../syntaxtree/Expressions.cpp ../syntaxtree/Statements.cpp ../syntaxtree/Declarations.cpp ../syntaxtree/Goal.cpp ../syntaxtree/MainClass.cpp)
set(VISITOR_SRCS ../visitor/SerializeVisitor.cpp)
set(GRAPH_SRCS ../graph/graph_lib/Graph.cpp)

add_executable(compiler
    main.cpp
    ${SYNTAX_TREE_SRCS}
    ${VISITOR_SRCS}
    ${GRAPH_SRCS}
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)
target_include_directories(compiler
    PRIVATE
        .
        ../graph/graph_lib
        ../visitor
        ../syntaxtree
        ${CMAKE_CURRENT_BINARY_DIR})
set_property(TARGET compiler
             PROPERTY CXX_STANDARD 17)


