#include <iostream>
#include <string>
// class InputChecker
// {
//     public:
//     static int inputInt(const std::string &message);
// };


class InputChecker
{
public:
    // Проверка, что ввод — это число
    static bool isNumericInput(int &number);

    // Проверка, что число в диапазоне
    static bool isInRange(int number, int min, int max);

    // Основная функция ввода
    static int inputInt(const std::string &message, int min = 1, int max = 7);
};
