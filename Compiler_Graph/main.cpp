#include <iostream>
#include "Graph.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Not enough arguments" << std::endl;
    } else {
        GraphProcessing::DirectedGraph myGraph(L"test_graph");

        myGraph.AddVertex(L"a");
        myGraph.AddVertex(L"b");
        myGraph.AddVertex(L"c");
        myGraph.AddVertex(L"d");

        myGraph.AddEdge(L"a", L"b", L"ab");
        myGraph.AddEdge(L"b", L"c", L"bc");
        myGraph.AddEdge(L"b", L"d", L"bd");

        std::string serializationPath = argv[1];
        std::wofstream serializationFile(serializationPath);
        GraphProcessing::GraphSerializer::GraphSerialize(myGraph, serializationFile);
    }
    return 0;
}