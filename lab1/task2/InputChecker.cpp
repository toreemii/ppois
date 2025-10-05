#include "InputChecker.h"
// int InputChecker::inputInt(const std::string &message)
// {
//     int number;
//     while (true)
//     {
//         std::cout << message;
//         std::cin >> number;
//         if(std::cin.fail()){
//             std::cin.clear();
//             std::cin.ignore(1000,'\n');
//             std::cout<<"Ошибка. Введено не число.\n";
//             continue;
//         }

//             if (number >= 1 && number <= 7)
//             {
//                 std::cin.ignore(1000, '\n');
//                 return number;
//             }
//         std::cin.clear();
//         std::cin.ignore(1000, '\n');
//         std::cout << "Введите целое число от 1 до 7.\n";
//     }
// }



#include "InputChecker.h"

bool InputChecker::isNumericInput(int &number)
{
    std::cin >> number;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Ошибка. Введено не число.\n";
        return false;
    }
    std::cin.ignore(1000, '\n');
    return true;
}

bool InputChecker::isInRange(int number, int min, int max)
{
    if (number < min || number > max)
    {
        std::cout << "Введите целое число от " << min << " до " << max << ".\n";
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
            continue; // Повторить ввод, если не число

        if (!isInRange(number, min, max))
            continue; // Повторить ввод, если вне диапазона

        return number;
    }
}
