#include "Graph.h"

#include <cassert>

namespace SyntaxTree {

    //-------------------GraphEdge------------------------------

    GraphEdge::GraphEdge(const std::wstring& _edgeName, const std::wstring& _fromVertexName, const std::wstring& _toVertexName)
    : edgeName(_edgeName),
      fromVertexName(_fromVertexName),
      toVertexName(_toVertexName)
      {}

    //-------------------DirectedGraph---------------------------

    DirectedGraph::~DirectedGraph() {
        std::vector<GraphEdge*> _edges;
        GetAllEdges(_edges);
        for (const GraphEdge* currEdge : _edges) {
            delete currEdge;
        }
        for (auto& verticesMapPair : vertices) {
            delete verticesMapPair.second;
        }
        vertices.clear();
    }

    void DirectedGraph::AddVertex(const std::wstring& vertexName) {
        assert(vertices.find(vertexName) == vertices.end());
        GraphVertex* newVertex = new GraphVertex();
        vertices.insert(std::make_pair(vertexName, newVertex));
    };

    void DirectedGraph::AddEdge(const std::wstring& fromVertexName, const std::wstring& toVertexName, const std::wstring& edgeName) {
        assert(vertices.find(fromVertexName) != vertices.end());
        assert(vertices.find(toVertexName) != vertices.end());

        GraphEdge* newEdge = new GraphEdge(edgeName, fromVertexName, toVertexName);

        GraphVertex* fromVertex = vertices[fromVertexName];
        GraphVertex* toVertex = vertices[toVertexName];
        fromVertex->outcomingEdges.push_back(newEdge);
        toVertex->incomingEdges.push_back(newEdge);
    }

    void DirectedGraph::GetAllVertices(std::vector<std::wstring>& _vertices) const {
        _vertices.clear();
        for (auto& verticesMapPair : vertices) {
            _vertices.push_back(verticesMapPair.first);
        }
    }

    const std::vector<GraphEdge*>& DirectedGraph::GetIncomingEdges(const std::wstring& vertexName) const {
        assert(vertices.find(vertexName) != vertices.end());
        return vertices.at(vertexName)->incomingEdges;
    }

    const std::vector<GraphEdge*>& DirectedGraph::GetOutcomingEdges(const std::wstring& vertexName) const {
        assert(vertices.find(vertexName) != vertices.end());
        return vertices.at(vertexName)->outcomingEdges;
    }

    void DirectedGraph::GetAllEdges(std::vector<GraphEdge*>& _edges) const {
        _edges.clear();
        std::vector<std::wstring> _vertices;
        GetAllVertices(_vertices);
        for (const std::wstring& currVertex : _vertices) {
            const std::vector<GraphEdge*>& currOutcomingEdges = GetOutcomingEdges(currVertex);
            _edges.insert(_edges.end(), currOutcomingEdges.begin(), currOutcomingEdges.end());
        }
    }

    //-------------------GraphSerializer----------------------------

    void GraphSerializer::GraphSerialize(const DirectedGraph& graph, std::wofstream& out) {
        out << L"digraph " << graph.GetName() << L" {" << L'\n';

        std::vector<std::wstring> _vertices;
        graph.GetAllVertices(_vertices);
        serializeVertices(_vertices, out);

        std::vector<GraphEdge*> _edges;
        graph.GetAllEdges(_edges);
        serializeEdges(_edges, out);

        out << L'}' << L'\n';
    }

    void GraphSerializer::serializeVertices(const std::vector<std::wstring>& _vertices, std::wofstream& out) {
        for (const std::wstring& currVertex : _vertices) {
            out << L'\t' << currVertex << L';' << L'\n';
        }
    }

    void GraphSerializer::serializeEdges(const std::vector<GraphEdge*>& _edges, std::wofstream& out) {
        for (const GraphEdge* currEdge : _edges) {
            out << L'\t' << currEdge->fromVertexName;
            out << L" -> ";
            out << currEdge->toVertexName;
            out << L" [label=" << currEdge->edgeName << L"]; " << L'\n';
        }
    }
}
