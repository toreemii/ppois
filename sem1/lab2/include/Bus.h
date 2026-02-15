#pragma once
#include "Vehicle.h"
#include <iostream>

class Bus : public Vehicle
{
    Bus(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status);
    void loadCargo(double weight) override;
    void unloadCargo(double wweight) override;
    void loadPeople(int people) override;
    void unloadPeople(int people) override;
    double calculateFuelConsumption(double distance) const override;
};