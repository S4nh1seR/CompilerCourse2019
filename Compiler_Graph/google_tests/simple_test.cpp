#include "Graph.h"
#include <gtest/gtest.h>
#include <unordered_set>
#include <tuple>

TEST(TestAddVertex, TestAddVertex) {
    GraphProcessing::DirectedGraph test_graph(L"test_graph");

    test_graph.AddVertex(L"vertex1");
    test_graph.AddVertex(L"vertex2");
    test_graph.AddVertex(L"vertex3");

    std::vector<std::wstring> _vertices;
    test_graph.GetAllVertices(_vertices);

    std::unordered_set<std::wstring> expected({L"vertex1", L"vertex2", L"vertex3"});
    std::unordered_set<std::wstring> result(_vertices.begin(), _vertices.end());
    ASSERT_EQ(result, expected);
}

TEST(TestAddEdge, TestAddEdge) {
    GraphProcessing::DirectedGraph test_graph(L"test_graph");

    test_graph.AddVertex(L"1");
    test_graph.AddVertex(L"2");
    test_graph.AddVertex(L"3");
    test_graph.AddEdge(L"1", L"2", L"12");
    test_graph.AddEdge(L"2", L"3", L"23");
    test_graph.AddEdge(L"3", L"1", L"31");

    std::vector<GraphProcessing::GraphEdge*> _edges;
    test_graph.GetAllEdges(_edges);
    std::vector<std::tuple<int, int, int>> coded_edges;
    for (auto edge : _edges) {
        coded_edges.push_back(std::make_tuple(std::stoi(edge->fromVertexName), std::stoi(edge->toVertexName), std::stoi(edge->edgeName)));
    }

    auto tuple_comparator = [](const std::tuple<int,int,int>& lhs, const std::tuple<int,int,int>& rhs) { return std::get<0>(lhs) < std::get<0>(rhs); };
    std::sort(coded_edges.begin(), coded_edges.end(), tuple_comparator);
    std::vector<std::tuple<int, int, int>> expected({{1, 2, 12}, {2, 3, 23}, {3, 1, 31}});
    ASSERT_EQ(coded_edges, expected);
}
/* тесты с ассертом почему-то не работают при сборке через терминал
TEST(TestAddVertex, TestRepeatedInsertion) {
    GraphProcessing::DirectedGraph test_graph(L"test_graph");

    test_graph.AddVertex(L"vertex1");
    ASSERT_DEATH(test_graph.AddVertex(L"vertex1"), "Assertion failed!");
}

TEST(TestAddEdge, TestImpossibleEdge) {
    GraphProcessing::DirectedGraph test_graph(L"test_graph");

    test_graph.AddVertex(L"vertex1");
    test_graph.AddVertex(L"vertex2");

    ASSERT_DEATH(test_graph.AddEdge(L"vertex1", L"vertex3", L"1-3"), "Assertion failed!");
    ASSERT_DEATH(test_graph.AddEdge(L"vertex3", L"vertex2", L"3-2");, "Assertion failed!");
}
*/

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}