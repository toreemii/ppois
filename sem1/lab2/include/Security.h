#pragma once
#include <string>
#include <ctime>
#include "Vehicle.h"
#include "Freight.h"
#include "Exceptions.h"
class Security
{
private:
    std::string securityId;
    int securityLevel;
    std::tm lastCheckDate;

public:
    Security(std::string securityId);
    bool checkVehicleSafety(Vehicle *vehicle);
    bool checkFreightSafety(Freight *freight);
    std::string getSecurityId();
    void logSecurityIncident() const;
    void updateSecurityLevel(int level);
};