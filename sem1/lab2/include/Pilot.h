#pragma once
#include "Employee.h"
#include "Reportable.h"

class Pilot : public Employee, public Reportable
{
public:
    Pilot(std::string employeeId, std::string firstName, std::string lastName);
    void submitTripReport(double distance, int hours, int minutes, int people, double cargo) override;
};