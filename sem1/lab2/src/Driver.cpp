#include "../include/Driver.h"

void Driver::submitTripReport(double distance, int hours, int minutes, int people, double cargo)
{
    std::cout << "Имя водителя: " << firstName << '\n';
    std::cout << "Фамилия водителя: " << lastName << '\n';
    std::cout << "Пройденный путь: " << distance << '\n';
    std::cout << "Затарчено часов: " << hours << '\n';
    std::cout << "Затрачено минут: " << minutes << '\n';
    std::cout << "Количество людей: " << people << '\n';
    std::cout << "Груз: " << cargo << '\n';
}

std::string Driver::getLicenseType()
{
    return licenseType;
}

void Driver::setLicenseType(const std::string &type)
{
    licenseType = type;
}
