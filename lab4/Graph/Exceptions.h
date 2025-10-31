#pragma once
#include <stdexcept>

struct IndexOutOfRange : public std::out_of_range
{
    IndexOutOfRange(const std::string &msg) : std::out_of_range("Ошибка: " + msg) {}
};
struct DuplicateVertex : public std::logic_error
{
    DuplicateVertex(const std::string &msg) : std::logic_error("Ошибка: " + msg) {}
};
struct InvalidEdge : public std::logic_error
{
    InvalidEdge(const std::string &msg) : std::logic_error("Ошибка: " + msg) {}
};
