#include "../include/Van.h"

Van::Van(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status)
    : Vehicle(fuel, maxSpeed, capacityPeople, capacityCargo, status) {}

void Van::loadCargo(double weight)
{
    if (weight <= capacityCargo)
    {
        currentCargo = weight;
    }
    else
    {
        throw InvalidWeightException();
    }
}

void Van::unloadCargo(double weignt)
{
    if (weignt >= currentCargo)
    {
        std::cout << "Ошибка:невозможно выгрузить больше груза, чем есть.";
        return;
    }
    else
    {
        currentCargo -= weignt;
    }
}

double Van::calculateFuelConsumption(double distance) const
{
    return (distance / 100) * 15;
}

double Van::estimateTravelTime(double distance) const
{
    return distance / maxSpeed;
}

void Van::updateOdometer(double distance)
{
    odometerReading += distance;
}

bool Van::checkMaintenanceDue() const
{
    time_t now = time(0);
    std::tm current = *localtime(&now);
    return difftime(mktime(&current), mktime(const_cast<std::tm *>(&lastMaintenanceDate))) > 31536000;
}

double Van::calculateTotalCost(double distance) const
{
    return calculateFuelConsumption(distance) * 0.8;
}

void Van::logTripStart() const
{
    std::cout << "Van trip started for vehicle " << vehicleId << std::endl;
}

void Van::logTripEnd() const
{
    std::cout << "Van trip ended for vehicle " << vehicleId << std::endl;
}

bool Van::verifyInsurance() const
{
    return isInsured;
}

void Van::adjustTirePressure(double pressure)
{
    tirePressure = pressure;
}

std::string Van::getVehicleDetails() const
{
    return "Van: Model " + model + ", Year " + std::to_string(manufactureYear);
}

void Van::performSelfCheck() const
{
    std::cout << "Van self-check: Fuel " << currentFuelLevel << ", Odometer " << odometerReading << std::endl;
}