#pragma once
#include <iterator>
#include <utility>

template <typename T>
class Graph;

template <typename T>
class EdgeIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::pair<size_t, size_t>;
    using reference = const value_type &;
    using pointer = const value_type *;
    using difference_type = std::ptrdiff_t;

    EdgeIterator(Graph<T> *g = nullptr, size_t i = 0, size_t j = 0) : graph(g), u(i), v(j), current({i, j})
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

    EdgeIterator &operator++()
    {
        ++v;
        moveForvard();
        return *this;
    }
    EdgeIterator operator++(int)
    {
        EdgeIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    EdgeIterator &operator--()
    {
        moveBack();
        return *this;
    }
    EdgeIterator operator--(int)
    {
        EdgeIterator tmp = *this;
        --(*this);
        return tmp;
    }

    bool operator==(const EdgeIterator &other) const
    {
        return graph == other.graph && u == other.u && v == other.v;
    }
    bool operator!=(const EdgeIterator &other) const
    {
        return !(*this == other);
    }

private:
    Graph<T> *graph;
    size_t u, v;
    value_type current;

    void moveForvard()
    {
        if (!graph || graph->vertex_count() == 0)
        {
            if (graph)
            {
                u = graph->vertex_count();
            }
            else
            {
                u = 0;
            }
            v = 0;
            return;
        }
        size_t n = graph->vertex_count();
        while (u < n)
        {
            while (v < n)
            {
                if (u < v && graph->has_edge(u, v))
                {
                    current = {u, v};
                    return;
                }
                ++v;
            }
            ++u;
            v = u + 1;
        }
        u = n;
        v = 0;
    }

    void moveBack()
    {
        if (!graph || graph->vertex_count() == 0)
        {
            u = 0;
            v = 0;
            return;
        }
        size_t n = graph->vertex_count();
        if (v > u + 1)
        {
            --v;
        }
        else
        {
            --u;
            v = n - 1;
        }
        while (u < n)
        {
            while (v > u)
            {
                if (graph->has_edge(u, v))
                {
                    current = {u, v};
                    return;
                }
                --v;
            }
            if (u == 0)
                break;
            --u;
            v = n - 1;
        }
        moveForvard();
    }

    friend class Graph<T>;
};
