#pragma once
#include <iostream>

template <typename T>
struct PrintVertex
{
    std::ostream &os;
    explicit PrintVertex(std::ostream &stream) : os(stream) {}
    void operator()(const T &v) const
    {
        os << v << " ";
    }
};

struct PrintEdge
{
    std::ostream &os;
    explicit PrintEdge(std::ostream &stream) : os(stream) {}
    void operator()(const std::pair<size_t, size_t> &edge) const
    {
        os << "(" << edge.first << "," << edge.second << ") ";
    }
};