#include "../include/Vehicle.h"

Vehicle::Vehicle(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status)
    : fuel(fuel), maxSpeed(maxSpeed), capacityPeople(capacityPeople), capacityCargo(capacityCargo), status(status) {}

std::string Vehicle::getVehicleId()
{
    return vehicleId;
}

void Vehicle::moveTo(double longitude, double latitude)
{
    this->location.setCoordinates(longitude, latitude);
}

std::tuple<double, double> Vehicle::getLocation()
{
    return this->location.getCoordinates();
}

std::string Vehicle::getStatus()
{
    return this->status.getStatus();
}

void Vehicle::setStatus(int statusState)
{
    status.setStatus(statusState);
}

void Vehicle::refuel(double amount)
{
    if (amount < 0)
    {
        throw FuelErrorException();
    }
    fuel->refuel(amount);
}

std::string Vehicle::getFuelType() const
{
    return fuel->getFuelType();
}

double Vehicle::getAvailableAmount() const
{
    return fuel->getAvailableAmount();
}

void Vehicle::assignDriver(Driver driver)
{
    if (driver.getLicenseType().empty())
    {
        throw DriverAssignmentException();
    }
    this->driver = driver;
}