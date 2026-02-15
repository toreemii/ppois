#pragma once
#include "Employee.h"
#include "Reportable.h"

class Conductor : public Employee, public Reportable
{
public:
    Conductor(std::string employeeId, std::string firstName, std::string lastName);
    void submitTripReport(double distance, int hours, int minutes, int people, double cargo) override;
};