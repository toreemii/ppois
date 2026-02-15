#pragma once
#include <string>
#include <tuple>
#include "Fuel.h"
#include "VehicleStatus.h"
#include "Driver.h"
#include "GPS.h"
#include "Exceptions.h"

class CargoTransport
{
public:
    virtual void loadCargo(double weight) = 0;
    virtual void unloadCargo(double weight) = 0;
};

class PassengerTransport
{
public:
    virtual void loadPeople(int people) = 0;
    virtual void unloadPeople(int people) = 0;
};

class FuelConsumable
{
public:
    virtual double calculateFuelConsumption(double distance) const = 0;
};

class IVehicle : public CargoTransport, public PassengerTransport, public FuelConsumable
{
public:
    virtual std::string getVehicleId() = 0;
    virtual void moveTo(double longitude, double latitude) = 0;
    virtual std::tuple<double, double> getLocation() = 0;
    virtual std::string getStatus() = 0;
    virtual void setStatus(int statusState) = 0;
    virtual void refuel(double amount) = 0;
    virtual std::string getFuelType() const = 0;
    virtual double getAvailableAmount() const = 0;
    virtual void assignDriver(Driver driver) = 0;
};