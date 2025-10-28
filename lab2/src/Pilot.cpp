#include "../include/Pilot.h"
#include <iostream>

Pilot::Pilot(std::string employeeId, std::string firstName, std::string lastName)
    : Employee(employeeId, firstName, lastName) {}

void Pilot::submitTripReport(double distance, int hours, int minutes, int people, double cargo)
{
    std::cout << "Отчет от кондуктора: " << distance << " км, " << hours << " ч " << minutes << " мин, " << people << " людей, " << cargo << " груза" << std::endl;
}