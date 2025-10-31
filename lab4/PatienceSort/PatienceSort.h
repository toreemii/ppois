#pragma once
#include <vector>

template <typename T>
void patienceSort(std::vector<T> &vec)
{
    if (vec.empty())
        return;

    std::vector<std::vector<T>> piles;

    for (int i = 0; i < vec.size(); ++i)
    {
        T value = vec[i];
        int pile_index = -1;

        for (int j = 0; j < piles.size(); ++j)
        {
            if (piles[j].back() > value)
            {
                pile_index = j;
                break;
            }
        }

        if (pile_index == -1)
        {
            piles.push_back({value});
        }
        else
        {
            piles[pile_index].push_back(value);
        }
    }

    std::vector<T> result;
    result.reserve(vec.size());

    while (!piles.empty())
    {
        int min_index = 0;
        T min_value = piles[0].back();

        for (int j = 1; j < piles.size(); ++j)
        {
            if (piles[j].back() < min_value)
            {
                min_value = piles[j].back();
                min_index = j;
            }
        }

        result.push_back(min_value);
        piles[min_index].pop_back();

        if (piles[min_index].empty())
        {
            piles[min_index] = piles.back();
            piles.pop_back();
        }
    }

    vec = result;
}

template <typename T, int N>
void patienceSort(T (&arr)[N])
{
    std::vector<T> vec(arr, arr + N);
    patienceSort(vec);
    for (int i = 0; i < N; ++i)
    {
        arr[i] = vec[i];
    }
}
