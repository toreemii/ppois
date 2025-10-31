#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void bubbleSort(T first, T last)
{
    if (first == last)
        return;
    for (T i = first; i != last; ++i)
    {
        for (T j = first; j != std::prev(last); ++j)
        {
            if (*std::next(j) < *j)
            {
                std::iter_swap(j, std::next(j));
            }
        }
    }
}

template <typename T, int N>
void bubbleSort(T (&arr)[N])
{
    bubbleSort(std::begin(arr), std::end(arr));
}

template <typename T>
void bubbleSort(std::vector<T> &vec)
{
    bubbleSort(vec.begin(), vec.end());
}