#pragma once
#include "Employee.h"
#include <iostream>

class Driver : public Employee
{
private:
    int drivingExperience;
    std::string preferredVehicleType;
    std::string licenseType;

public:
    Driver() {}
    Driver(const std::string &firstName, const std::string &lastName, const std::string &licenseType, int drivingExperience = 0,
           const std::string &preferredVehicleType = "") : Employee("DRV1", firstName, lastName), licenseType(licenseType),
                                                           drivingExperience(drivingExperience), preferredVehicleType(preferredVehicleType) {}
    void submitTripReport(double distance, int hours, int minutes, int people, double cargo);
    std::string getLicenseType();
    void setLicenseType(const std::string &type);
};