#include "Scanner.h"
#include "parser.tab.hh"
#include <Goal.h>
#include <Graph.h>
#include <SerializeVisitor.h>
#include <iostream>

void serializeGraph(std::istream& in, std::wostream& out = std::wcout) {
    auto lexer = std::make_unique<Scanner>();
    lexer->switch_streams(in, std::cerr);
    std::unique_ptr<const SyntaxTree::Goal> syntaxTreeRoot;
    yy::Parser parser(syntaxTreeRoot, lexer);
    parser.parse();

    SerializeVisitor visitor;
    auto graph = std::make_shared<SyntaxTree::DirectedGraph>(L"SyntaxTreeGraph");
    visitor.RoundLaunch(graph, syntaxTreeRoot.release());
    SyntaxTree::GraphSerializer::GraphSerialize(*graph, out);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        serializeGraph(std::cin);
    } else {
        std::ifstream in(argv[1]);
        if (argc < 3) {
            serializeGraph(in);
        } else {
            std::wofstream out(argv[2]);
            serializeGraph(in, out);
        }
    }
}

