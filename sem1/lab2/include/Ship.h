#pragma once
#include "Vehicle.h"

class Ship : public Vehicle
{
private:
    double currentCargo;
    int currentPeople;
    double odometerReading;
    double tirePressure;
    bool isInsured;
    std::tm lastMaintenanceDate;

public:
    Ship(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status);
    void loadCargo(double weight);
    void unloadCargo(double weight);
    void loadPeople(int people);
    void unloadPeople(int people);
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
    double getCurrentCargo();
    int getCurrentPeople();
    double getOdometerReading();
    double getTirePressure();
};
