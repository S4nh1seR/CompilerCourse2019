#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace SyntaxTree {

    struct GraphEdge {
        GraphEdge(const std::wstring& _edgeName, const std::wstring& _fromVertexName, const std::wstring& _toVertexName);

        std::wstring edgeName;
        std::wstring fromVertexName;
        std::wstring toVertexName;
    };

    class DirectedGraph {
    public:
        DirectedGraph(const std::wstring& _graphName = L"g"): graphName(_graphName) {}
        ~DirectedGraph();

        void AddVertex(const std::wstring& vertexName);
        void AddEdge(const std::wstring& fromVertexName, const std::wstring& toVertexName, const std::wstring& edgeName = L"");

        const std::vector<GraphEdge*>& GetIncomingEdges(const std::wstring& vertexName) const;
        const std::vector<GraphEdge*>& GetOutcomingEdges(const std::wstring& vertexName) const;

        void GetAllVertices(std::vector<std::wstring>& _vertices) const;
        void GetAllEdges(std::vector<GraphEdge*>& _edges) const;

        const std::wstring& GetName() const { return graphName; }
    private:
        struct GraphVertex {
            std::vector<GraphEdge*> incomingEdges;
            std::vector<GraphEdge*> outcomingEdges;
        };

        std::unordered_map<std::wstring, GraphVertex*> vertices;
        std::wstring graphName;
    };

    class GraphSerializer {
    public:
        static void GraphSerialize(const DirectedGraph& graph, std::wostream& out);

    private:
        static void serializeVertices(const std::vector<std::wstring>& _vertices, std::wostream& out);
        static void serializeEdges(const std::vector<GraphEdge*>& _edges, std::wostream& out);
    };
}
