#include "../include/Captain.h"
#include <iostream>

Captain::Captain(std::string employeeId, std::string firstName, std::string lastName)
    : Employee(employeeId, firstName, lastName) {}

void Captain::submitTripReport(double distance, int hours, int minutes, int people, double cargo)
{
    std::cout << "Имя капитана: " << firstName << '\n';
    std::cout << "Фамилия капитана: " << lastName << '\n';
    std::cout << "Пройденный путь: " << distance << '\n';
    std::cout << "Затарчено часов: " << hours << '\n';
    std::cout << "Затрачено минут: " << minutes << '\n';
    std::cout << "Количество людей: " << people << '\n';
    std::cout << "Груз: " << cargo << '\n';
}