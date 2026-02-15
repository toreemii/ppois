#pragma once
#include "Vehicle.h"
#include <iostream>

class Car : public Vehicle
{
public:
    Car(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status);
    void loadCargo(double weight) override;
    void unloadCargo(double weight) override;
    void loadPeople(int people) override;
    void unloadPeople(int people) override;
    double calculateFuelConsumption(double distance) const override;
};