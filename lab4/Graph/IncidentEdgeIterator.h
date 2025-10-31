#pragma once
#include <iterator>

template <typename T>
class Graph;

template <typename T>
class IncidentEdgeIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair<size_t, size_t>;
    using reference = const value_type &;
    using pointer = const value_type *;
    using difference_type = std::ptrdiff_t;

    IncidentEdgeIterator(Graph<T> *g = nullptr, size_t vertex = 0, size_t neighbor = 0)
        : graph(g), initialVertex(vertex), currentNeighbor(neighbor)
    {
        if (graph)
            moveForvard();
    }

    reference operator*() const
    {
        return current;
    }
    pointer operator->() const
    {
        return &current;
    }

    IncidentEdgeIterator &operator++()
    {
        ++currentNeighbor;
        moveForvard();
        return *this;
    }
    IncidentEdgeIterator operator++(int)
    {
        IncidentEdgeIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    IncidentEdgeIterator &operator--()
    {
        moveBack();
        return *this;
    }
    IncidentEdgeIterator operator--(int)
    {
        IncidentEdgeIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const IncidentEdgeIterator &other) const
    {
        return graph == other.graph && initialVertex == other.initialVertex && currentNeighbor == other.currentNeighbor;
    }
    bool operator!=(const IncidentEdgeIterator &other) const
    {
        return !(*this == other);
    }

private:
    Graph<T> *graph;
    size_t initialVertex;
    size_t currentNeighbor;
    value_type current;

    void moveForvard()
    {
        if (!graph)
            return;
        size_t n = graph->vertex_count();
        while (currentNeighbor < n)
        {
            if (graph->has_edge(initialVertex, currentNeighbor))
            {
                if (initialVertex < currentNeighbor)
                    current = std::make_pair(initialVertex, currentNeighbor);
                else
                    current = std::make_pair(currentNeighbor, initialVertex);
                return;
            }
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
            if (graph->has_edge(initialVertex, currentNeighbor))
            {
                if (initialVertex < currentNeighbor)
                    current = std::make_pair(initialVertex, currentNeighbor);
                else
                    current = std::make_pair(currentNeighbor, initialVertex);
                return;
            }
            --currentNeighbor;
        }
    }

    friend class Graph<T>;
};
