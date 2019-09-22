set(HEADER_FILES Graph.h)
set(SOURCE_FILES Graph.cpp)
add_library(graph_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(Compiler_Graph::graph_lib ALIAS graph_lib)

