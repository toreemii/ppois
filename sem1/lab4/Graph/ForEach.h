#pragma once

template <typename Input, typename Function>
void forEach(Input first, Input last, Function func)
{
    while (first != last)
    {
        func(*first);
        first++;
    }
}