#pragma once
#include <vector>

template <typename T>
bool isSorted(const std::vector<T> &container)
{
    if (container.empty())
        return true;
    for (int i = 1; i < container.size(); ++i)
    {
        if (container[i] < container[i - 1])
        {
            return false;
        }
    }
    return true;
}

template <typename T, int N>
bool isSorted(const T (&container)[N])
{
    if (N == 0)
        return true;
    for (int i = 1; i < N; ++i)
    {
        if (container[i] < container[i - 1])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool isSorted(T first, T last)
{
    if (first == last)
        return true;
    T next = first;
    ++next;
    while (next != last)
    {
        if (*next < *first)
        {
            return false;
        }
        ++first;
        ++next;
    }
    return true;
}

template <typename T, int N>
void printArray(const T (&arr)[N])
{
    for (int i = 0; i < N; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void printVector(const std::vector<T> &vec)
{
    for (const auto &item : vec)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}