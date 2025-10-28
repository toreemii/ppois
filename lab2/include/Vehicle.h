#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "IVehicle.h"
#include "Fuel.h"

class Vehicle : public IVehicle
{
protected:
    std::string vehicleId;
    Fuel *fuel;
    double maxSpeed;
    int capacityPeople;
    double capacityCargo;
    VehicleStatus status;
    GPS location;
    Driver driver;
    double currentCargo;
    int currentPeople;

public:
    Vehicle(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status);
    std::string getVehicleId() override;
    void moveTo(double longitude, double latitude) override;
    std::tuple<double, double> getLocation() override;
    std::string getStatus() override;
    void setStatus(int statusState) override;
    void refuel(double amount) override;
    std::string getFuelType() const override;
    double getAvailableAmount() const override;
    void assignDriver(Driver driver) override;
    void loadCargo(double weight) override = 0;
    void unloadCargo(double weight) override = 0;
    void loadPeople(int people) override = 0;
    void unloadPeople(int people) override = 0;
    double calculateFuelConsumption(double distance) const override = 0;
};