#include "Graph.h"
#include <gtest/gtest.h>

TEST(GraphTest, VertexAndEdgeCount)
{
    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_edge(0, 1);
    EXPECT_EQ(g.vertex_count(), 2);
    EXPECT_EQ(g.edge_count(), 1);
}

TEST(GraphTest, AddAndRemoveVertex)
{
    Graph<int> g;
    g.add_vertex(5);
    g.add_vertex(10);
    EXPECT_EQ(g.vertex_count(), 2);
    g.remove_vertex(0);
    EXPECT_EQ(g.vertex_count(), 1);
}

TEST(GraphTest, HasEdge)
{
    Graph<int> g;
    g.add_vertex(3);
    g.add_vertex(7);
    g.add_edge(0, 1);
    EXPECT_TRUE(g.has_edge(0, 1));
    g.remove_edge(0, 1);
    EXPECT_FALSE(g.has_edge(0, 1));
}

TEST(GraphTest, DegreeCalculation)
{
    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    EXPECT_EQ(g.degree(0), 2);
    EXPECT_EQ(g.degree(1), 1);
}

TEST(GraphTest, EqualityOperators)
{
    Graph<int> g1, g2;
    g1.add_vertex(1);
    g2.add_vertex(1);
    EXPECT_TRUE(g1 == g2);
    g2.add_vertex(2);
    EXPECT_TRUE(g1 != g2);
}

TEST(GraphTest, EdgeIteratorOperations)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    int edge_count = 0;
    for (auto it = graph.edges_begin(); it != graph.edges_end(); ++it)
    {
        edge_count++;
    }
    EXPECT_EQ(edge_count, 3);
}

TEST(GraphTest, IncidentEdgeIteratorOperations)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(0, 3);
    int incident_count = 0;
    for (auto it = graph.incident_begin(0); it != graph.incident_end(0); ++it)
    {
        incident_count++;
    }
    EXPECT_EQ(incident_count, 3);
}

TEST(GraphTest, AdjacencyIteratorOperations)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(0, 3);
    int adjacent_count = 0;
    for (auto it = graph.adjacent_begin(0); it != graph.adjacent_end(0); ++it)
    {
        adjacent_count++;
        EXPECT_TRUE(*it == 1 || *it == 2 || *it == 3);
    }
    EXPECT_EQ(adjacent_count, 3);
}

TEST(GraphTest, ExceptionsTest)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    EXPECT_THROW(graph.has_edge(10, 0), IndexOutOfRange);
    EXPECT_THROW(graph.add_edge(10, 0), IndexOutOfRange);
    EXPECT_THROW(graph.remove_vertex(10), IndexOutOfRange);
    EXPECT_THROW(graph.degree(10), IndexOutOfRange);
    EXPECT_THROW(graph.add_vertex("A"), DuplicateVertex);
    EXPECT_THROW(graph.add_edge(0, 0), InvalidEdge);
    EXPECT_THROW(graph.edge_degree(0, 2), InvalidEdge);
}

TEST(GraphTest, VertexIterators)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    int count = 0;
    for (auto it = graph.begin(); it != graph.end(); ++it)
    {
        count++;
    }
    EXPECT_EQ(count, 4);
    const auto &const_graph = graph;
    count = 0;
    for (auto it = const_graph.begin(); it != const_graph.end(); ++it)
    {
        count++;
    }
    EXPECT_EQ(count, 4);
    count = 0;
    for (auto it = graph.rbegin(); it != graph.rend(); ++it)
    {
        count++;
    }
    EXPECT_EQ(count, 4);
}

TEST(GraphTest, EdgeDegreeTest)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 2);
    EXPECT_EQ(graph.edge_degree(0, 1), 1);
}

TEST(GraphTest, OutputOperatorTest)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    std::stringstream ss;
    ss << graph;
    std::string output = ss.str();
    EXPECT_TRUE(output.find("Вершины") != std::string::npos);
    EXPECT_TRUE(output.find("Ребра") != std::string::npos);
}

TEST(GraphTest, IteratorRemoveOperations)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_vertex("D");
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    auto vertex_it = graph.begin();
    vertex_it = graph.remove_vertex(vertex_it);
    EXPECT_EQ(graph.vertex_count(), 3);
}

TEST(GraphTest, EmptyGraphOperations)
{
    Graph<std::string> empty_graph;
    EXPECT_TRUE(empty_graph.empty());
    EXPECT_EQ(empty_graph.vertex_count(), 0);
    EXPECT_EQ(empty_graph.edge_count(), 0);
    EXPECT_EQ(empty_graph.begin(), empty_graph.end());
    EXPECT_EQ(empty_graph.edges_begin(), empty_graph.edges_end());
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.clear();
    EXPECT_TRUE(graph.empty());
    EXPECT_EQ(graph.vertex_count(), 0);
}

TEST(GraphTest, EdgeIteratorDetailed)
{
    Graph<std::string> graph;
    graph.add_vertex("X");
    graph.add_vertex("Y");
    graph.add_vertex("Z");
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    auto it = graph.edges_begin();
    std::vector<std::pair<size_t, size_t>> edges;
    while (it != graph.edges_end())
    {
        edges.push_back(*it);
        ++it;
    }
    EXPECT_EQ(edges.size(), 2);
}

TEST(GraphTest, PrintFunctionsTest)
{
    std::stringstream ss;
    PrintVertex<std::string> pv(ss);
    pv("TestVertex");
    EXPECT_TRUE(ss.str().find("TestVertex") != std::string::npos);
    ss.str("");
    PrintEdge pe(ss);
    pe({1, 2});
    EXPECT_TRUE(ss.str().find("(1,2)") != std::string::npos);
}

TEST(GraphTest, ForEachTest)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    std::vector<std::string> collected;
    auto collector = [&collected](const std::string &v)
    {
        collected.push_back(v);
    };
    graph.forEach(collector);
    EXPECT_EQ(collected.size(), 3);
    EXPECT_EQ(collected[0], "A");
}

TEST(GraphTest, ComparisonOperators)
{
    Graph<std::string> g1, g2, g3;
    g1.add_vertex("A");
    g2.add_vertex("A");
    g2.add_vertex("B");
    g3.add_vertex("A");
    EXPECT_TRUE(g1 <= g2);
    EXPECT_TRUE(g2 >= g1);
    EXPECT_TRUE(g1 <= g3);
    EXPECT_TRUE(g1 >= g3);
}

TEST(GraphTest, EdgeIteratorEdgeCases)
{
    Graph<std::string> empty_graph;
    EXPECT_EQ(empty_graph.edges_begin(), empty_graph.edges_end());
    Graph<std::string> single_vertex;
    single_vertex.add_vertex("X");
    EXPECT_EQ(single_vertex.edges_begin(), single_vertex.edges_end());
    Graph<std::string> no_edges;
    no_edges.add_vertex("A");
    no_edges.add_vertex("B");
    EXPECT_EQ(no_edges.edges_begin(), no_edges.edges_end());
}

TEST(GraphTest, DifferentDataTypes)
{
    Graph<int> int_graph;
    int_graph.add_vertex(1);
    int_graph.add_vertex(2);
    int_graph.add_edge(0, 1);
    Graph<double> double_graph;
    double_graph.add_vertex(1.5);
    double_graph.add_vertex(2.5);
    double_graph.add_edge(0, 1);
    EXPECT_EQ(int_graph.edge_count(), 1);
    EXPECT_EQ(double_graph.edge_count(), 1);
}

TEST(GraphTest, CopyConstructorAndAssignment)
{
    Graph<std::string> graph1;
    graph1.add_vertex("A");
    graph1.add_vertex("B");
    graph1.add_edge(0, 1);
    Graph<std::string> graph2 = graph1;
    EXPECT_EQ(graph2.vertex_count(), 2);
    EXPECT_EQ(graph2.edge_count(), 1);
    Graph<std::string> graph3;
    graph3 = graph1;
    EXPECT_EQ(graph3.vertex_count(), 2);
    EXPECT_EQ(graph3.edge_count(), 1);
}

TEST(GraphTest, MoveSemantics)
{
    Graph<std::string> graph1;
    graph1.add_vertex("A");
    graph1.add_vertex("B");
    Graph<std::string> graph2 = std::move(graph1);
    EXPECT_EQ(graph2.vertex_count(), 2);
    EXPECT_EQ(graph2.edge_count(), 1);
    Graph<std::string> graph3;
    graph3 = std::move(graph2);
    EXPECT_EQ(graph3.vertex_count(), 2);
    EXPECT_EQ(graph3.edge_count(), 1);
}

TEST(GraphTest, ConstIterators)
{
    Graph<std::string> graph;
    graph.add_vertex("A");
    graph.add_vertex("B");
    graph.add_vertex("C");
    graph.add_edge(0, 1);
    const Graph<std::string> &const_graph = graph;
    int edge_count = 0;
    for (auto it = const_graph.edges_begin(); it != const_graph.edges_end(); ++it)
    {
        edge_count++;
    }
    EXPECT_EQ(edge_count, 1);
    int adj_count = 0;
    for (auto it = const_graph.adjacent_begin(0); it != const_graph.adjacent_end(0); ++it)
    {
        adj_count++;
    }
    EXPECT_EQ(adj_count, 1);
    int inc_count = 0;
    for (auto it = const_graph.incident_begin(0); it != const_graph.incident_end(0); ++it)
    {
        inc_count++;
    }
    EXPECT_EQ(inc_count, 1);
}
