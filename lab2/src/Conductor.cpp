#include "../include/Conductor.h"
#include <iostream>

Conductor::Conductor(std::string employeeId, std::string firstName, std::string lastName)
    : Employee(employeeId, firstName, lastName) {}

void Conductor::submitTripReport(double distance, int hours, int minutes, int people, double cargo)
{
    std::cout << "Отчет от кондуктора: " << distance << " км, " << hours << " ч " << minutes << " мин, " << people << " людей, " << cargo << " груза" << std::endl;
}