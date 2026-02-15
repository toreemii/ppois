#pragma once
#include <iterator>

template <typename T>
class Graph;

template <typename T>
class AdjacencyIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = size_t;
    using reference = const value_type &;
    using pointer = const value_type *;
    using difference_type = std::ptrdiff_t;

    AdjacencyIterator(Graph<T> *g = nullptr, size_t vertex = 0, size_t neighbor = 0)
        : graph(g), initialVertex(vertex), currentNeighbor(neighbor)
    {
        if (graph)
            moveForvard();
    }

    reference operator*() const
    {
        return currentNeighbor;
    }
    pointer operator->() const
    {
        return &currentNeighbor;
    }

    AdjacencyIterator &operator++()
    {
        ++currentNeighbor;
        moveForvard();
        return *this;
    }
    AdjacencyIterator operator++(int)
    {
        AdjacencyIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    AdjacencyIterator &operator--()
    {
        moveBack();
        return *this;
    }
    AdjacencyIterator operator--(int)
    {
        AdjacencyIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const AdjacencyIterator &other) const
    {
        return graph == other.graph && initialVertex == other.initialVertex && currentNeighbor == other.currentNeighbor;
    }
    bool operator!=(const AdjacencyIterator &other) const
    {
        return !(*this == other);
    }

private:
    Graph<T> *graph;
    size_t initialVertex;
    size_t currentNeighbor;

    void moveForvard()
    {
        if (!graph)
            return;
        size_t n = graph->vertex_count();
        while (currentNeighbor < n)
        {
            if (currentNeighbor != initialVertex && graph->has_edge(initialVertex, currentNeighbor))
                return;
            ++currentNeighbor;
        }
    }

    void moveBack()
    {
        if (!graph)
            return;
        if (currentNeighbor == 0)
        {
            currentNeighbor = graph->vertex_count();
            return;
        }
        --currentNeighbor;
        while (currentNeighbor > 0)
        {
            if (currentNeighbor != initialVertex && graph->has_edge(initialVertex, currentNeighbor))
                return;
            --currentNeighbor;
        }
    }

    friend class Graph<T>;
};
