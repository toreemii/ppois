#include <iostream>
#include <string>

class InputChecker
{
public:
    static bool isNumericInput(int &number);
    static bool isInRange(int number, int min, int max);
    static int inputInt(const std::string &message, int min = 1, int max = 10);
};
