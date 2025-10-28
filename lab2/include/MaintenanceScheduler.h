#pragma once
#include <string>
#include "Maintenance.h"
#include "Vehicle.h"
class MaintenanceScheduler
{
private:
    std::string schedulerId;

public:
    MaintenanceScheduler(std::string schedulerId);
    std::string getSchedulerId();
    void scheduleMaintenance(Vehicle *vehicle, Maintenance *maintenance);
};