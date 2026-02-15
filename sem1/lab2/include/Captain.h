#pragma once
#include "Employee.h"
#include "Reportable.h"

class Captain : public Employee, public Reportable
{
public:
    Captain(std::string employeeId, std::string firstName, std::string lastName);
    void submitTripReport(double distance, int hours, int minutes, int people, double cargo) override;
};