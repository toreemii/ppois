#pragma once
#include <vector>
#include <iostream>
#include "Vehicle.h"
#include "Freight.h"
#include "Maintenance.h"
#include <algorithm>

class Depot
{
private:
    std::string depotId;
    std::vector<Vehicle *> vehicles;
    std::vector<Freight *> inventory;

public:
    Depot(std::string depotId);
    void addVehicle(Vehicle *vehicle);
    void loadFreight(Freight *freight, Vehicle *vehicle);
    void scheduleMaintenance(Vehicle *vehicle, Maintenance *maintenance);
    std::string getDepoId();
    std::vector<Vehicle *> getVehicles();
    void removeVehicle(Vehicle *vehicle);
};