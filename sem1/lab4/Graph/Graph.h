#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "ForEach.h"
#include "Exceptions.h"
#include "Print.h"
#include "EdgeIterator.h"
#include "IncidentEdgeIterator.h"
#include "AdjacencyIterator.h"

template <typename T>
class Graph
{
public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = size_t;
    using edge_type = std::pair<size_type, size_type>;

    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using reverse_iterator = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

    using edge_iterator = EdgeIterator<T>;
    using const_edge_iterator = EdgeIterator<T>;
    using adjacency_iterator = AdjacencyIterator<T>;
    using const_adjacency_iterator = AdjacencyIterator<T>;
    using incident_edge_iterator = IncidentEdgeIterator<T>;
    using const_incident_edge_iterator = IncidentEdgeIterator<T>;

private:
    std::vector<T> vertices;
    std::vector<std::vector<bool>> adjacency;

public:
    Graph() = default;
    Graph(const Graph &other) = default;
    Graph &operator=(const Graph &other) = default;
    ~Graph() = default;

    bool empty() const
    {
        return vertices.empty();
    }

    void clear()
    {
        vertices.clear();
        adjacency.clear();
    }

    size_type vertex_count() const
    {
        return vertices.size();
    }

    size_type edge_count() const
    {
        size_type count = 0;
        for (size_type i = 0; i < adjacency.size(); i++)
            for (size_type j = i + 1; j < adjacency.size(); j++)
                if (adjacency[i][j])
                    count++;
        return count;
    }

    bool has_vertex(const T &v) const
    {
        return std::find(vertices.begin(), vertices.end(), v) != vertices.end();
    }

    bool has_edge(size_type i, size_type j) const
    {
        if (i >= vertex_count() || j >= vertex_count())
            throw IndexOutOfRange("Некорректный индекс вершины");
        return adjacency[i][j];
    }

    void add_vertex(const T &value)
    {
        if (has_vertex(value))
            throw DuplicateVertex("Вершина уже существует");

        vertices.push_back(value);
        for (auto &row : adjacency)
            row.push_back(false);
        adjacency.emplace_back(vertex_count(), false);
    }

    void add_edge(size_type i, size_type j)
    {
        if (i >= vertex_count() || j >= vertex_count())
            throw IndexOutOfRange("Некорректный индекс вершины");
        if (i == j)
            throw InvalidEdge("Петли не допускаются");
        adjacency[i][j] = adjacency[j][i] = true;
    }

    void remove_vertex(size_type index)
    {
        if (index >= vertex_count())
            throw IndexOutOfRange("Некорректный индекс вершины");
        vertices.erase(vertices.begin() + index);
        adjacency.erase(adjacency.begin() + index);
        for (auto &row : adjacency)
            row.erase(row.begin() + index);
    }

    void remove_edge(size_type i, size_type j)
    {
        if (i >= vertex_count() || j >= vertex_count())
            throw IndexOutOfRange("Некорректный индекс вершины");
        adjacency[i][j] = adjacency[j][i] = false;
    }

    size_type degree(size_type v) const
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("Некорректный индекс вершины");
        size_type deg = 0;
        for (size_type i = 0; i < vertex_count(); ++i)
            if (adjacency[v][i])
                ++deg;
        return deg;
    }

    size_type edge_degree(size_type u, size_type v) const
    {
        if (u >= vertex_count() || v >= vertex_count())
            throw IndexOutOfRange("Некорректный индекс вершины");
        if (!adjacency[u][v])
            throw InvalidEdge("Ребро не существует");
        size_type count = 0;
        for (size_type i = 0; i < vertex_count(); ++i)
            if (i != u && i != v && adjacency[u][i] && adjacency[v][i])
                ++count;
        return count;
    }

    iterator begin()
    {
        return vertices.begin();
    }
    iterator end()
    {
        return vertices.end();
    }
    const_iterator begin() const
    {
        return vertices.begin();
    }
    const_iterator end() const
    {
        return vertices.end();
    }
    reverse_iterator rbegin()
    {
        return vertices.rbegin();
    }
    reverse_iterator rend()
    {
        return vertices.rend();
    }
    const_reverse_iterator rbegin() const
    {
        return vertices.rbegin();
    }
    const_reverse_iterator rend() const
    {
        return vertices.rend();
    }

    edge_iterator edges_begin() noexcept
    {
        return edge_iterator(this, 0, 1);
    }
    edge_iterator edges_end() noexcept
    {
        return edge_iterator(this, vertex_count(), 0);
    }
    const_edge_iterator edges_begin() const noexcept
    {
        return edge_iterator(const_cast<Graph *>(this), 0, 1);
    }
    const_edge_iterator edges_end() const noexcept
    {
        return edge_iterator(const_cast<Graph *>(this), vertex_count(), 0);
    }

    adjacency_iterator adjacent_begin(size_type v)
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("adjacent_begin: некорректный индекс вершины");
        return adjacency_iterator(this, v, 0);
    }
    adjacency_iterator adjacent_end(size_type v)
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("adjacent_end: некорректный индекс вершины");
        return adjacency_iterator(this, v, vertex_count());
    }
    const_adjacency_iterator adjacent_begin(size_type v) const
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("adjacent_begin: некорректный индекс вершины");
        return adjacency_iterator(const_cast<Graph *>(this), v, 0);
    }
    const_adjacency_iterator adjacent_end(size_type v) const
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("adjacent_end: некорректный индекс вершины");
        return adjacency_iterator(const_cast<Graph *>(this), v, vertex_count());
    }

    incident_edge_iterator incident_begin(size_type v)
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("incident_begin: некорректный индекс вершины");
        return incident_edge_iterator(this, v, 0);
    }
    incident_edge_iterator incident_end(size_type v)
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("incident_end: некорректный индекс вершины");
        return incident_edge_iterator(this, v, vertex_count());
    }
    const_incident_edge_iterator incident_begin(size_type v) const
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("incident_begin: некорректный индекс вершины");
        return incident_edge_iterator(const_cast<Graph *>(this), v, 0);
    }
    const_incident_edge_iterator incident_end(size_type v) const
    {
        if (v >= vertex_count())
            throw IndexOutOfRange("incident_end: некорректный индекс вершины");
        return incident_edge_iterator(const_cast<Graph *>(this), v, vertex_count());
    }

    template <typename Function>
    void forEach(Function func) const
    {
        ::forEach(vertices.begin(), vertices.end(), func);
    }

    template <typename Function>
    void for_each_vertex(Function func) const
    {
        for (const auto &vertex : vertices)
        {
            func(vertex);
        }
    }

    bool operator==(const Graph &other) const
    {
        return vertices == other.vertices && adjacency == other.adjacency;
    }

    bool operator!=(const Graph &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Graph &other) const
    {
        return vertex_count() < other.vertex_count();
    }

    bool operator>(const Graph &other) const
    {
        return vertex_count() > other.vertex_count();
    }

    bool operator<=(const Graph &other) const
    {
        return !(*this > other);
    }

    bool operator>=(const Graph &other) const
    {
        return !(*this < other);
    }

    friend std::ostream &operator<<(std::ostream &os, const Graph<T> &g)
    {
        os << "Вершины (" << g.vertex_count() << "): ";
        g.for_each_vertex(PrintVertex<T>(os));

        os << "\nРебра (" << g.edge_count() << "): ";
        PrintEdge printEdge(os);
        for (auto it = g.edges_begin(); it != g.edges_end(); ++it)
        {
            printEdge(*it);
        }
        return os;
    }

    iterator remove_vertex(iterator it)
    {
        if (it == vertices.end())
            throw IndexOutOfRange("remove_vertex(iterator): end iterator");
        size_type idx = static_cast<size_type>(std::distance(vertices.begin(), it));
        remove_vertex(idx);
        if (idx >= vertex_count())
            return vertices.end();
        return vertices.begin() + idx;
    }

    edge_iterator remove_edge(edge_iterator it)
    {
        auto [u, v] = *it;
        remove_edge(u, v);
        return ++it;
    }
};
