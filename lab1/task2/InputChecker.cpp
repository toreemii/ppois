#include "InputChecker.h"

bool InputChecker::isNumericInput(int &number)
{
    std::cin >> number;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Ошибка. Введите число.\n";
        return false;
    }
    std::cin.ignore(1000, '\n');
    return true;
}

bool InputChecker::isInRange(int number, int min, int max)
{
    if (number < min || number > max)
    {
        return false;
    }
    return true;
}

int InputChecker::inputInt(const std::string &message, int min, int max)
{
    int number;
    while (true)
    {
        std::cout << message;
        if (!isNumericInput(number))
        if (!isInRange(number, min, max))
            continue;
        return number;
    }
}
