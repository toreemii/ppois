#include "Graph.h"
#include <iostream>

int main()
{
    Graph<std::string> g;

    g.add_vertex("A");
    g.add_vertex("B");
    g.add_vertex("C");

    g.add_edge(0, 1);
    g.add_edge(1, 2);

    std::cout << g << std::endl;

    std::cout << "Количество вершин: " << g.vertex_count() << std::endl;
    std::cout << "Количество рёбер: " << g.edge_count() << std::endl;

    g.remove_edge(1, 2);
    g.remove_vertex(0);

    std::cout << "\nПосле удаления:\n" << g << std::endl;

    return 0;
}
