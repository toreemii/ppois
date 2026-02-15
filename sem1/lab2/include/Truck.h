#pragma once
#include "Vehicle.h"

class Truck : public Vehicle
{
public:
    Truck(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status);
    void loadCargo(double weight);
    void unloadCargo(double weight);
    virtual void loadPeople(int people) {}
    virtual void unloadPeople(int people) {}
    double calculateFuelConsumption(double distance) const;
    double estimateTravelTime(double distance) const;
    void updateOdometer(double distance);
    bool checkMaintenanceDue() const;
    double calculateTotalCost(double distance) const;
    void logTripStart() const;
    void logTripEnd() const;
    bool verifyInsurance() const;
    void adjustTirePressure(double pressure);
    std::string getVehicleDetails() const;
    void performSelfCheck() const;
};