#pragma once
#include <string>
#include "Freight.h"
#include "Vehicle.h"
class Insurance
{
private:
    std::string insuranceId;
    double coverageAmount;

public:
    Insurance(std::string insuranceId, double coverageAmount);
    void insureFreight(Freight *freight);
    void insureVehicle(Vehicle *vehicle);
    std::string getInsuranceId();
};