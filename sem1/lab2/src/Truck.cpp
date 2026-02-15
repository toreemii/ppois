#include "../include/Truck.h"

Truck::Truck(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status)
    : Vehicle(fuel, maxSpeed, capacityPeople, capacityCargo, status) {}

void Truck::loadCargo(double weight)
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

void Truck::unloadCargo(double weignt)
{
    if (weignt >= currentCargo)
    {
        std::cout << "Ошибка: невозможно выгрузить больше груза, чем есть.";
        return;
    }
    else
    {
        currentCargo -= weignt;
    }
}

double Truck::calculateFuelConsumption(double distance) const
{
    return (distance / 100) * 20;
}

double Truck::estimateTravelTime(double distance) const
{
    return distance / maxSpeed;
}

double Truck::calculateTotalCost(double distance) const
{
    return calculateFuelConsumption(distance) * 1.0;
}

void Truck::logTripStart() const
{
    std::cout << "Началaсь поездка на грузовике для транспортного средства " << vehicleId << std::endl;
}

void Truck::logTripEnd() const
{
    std::cout << "Поездка на грузовике завершена для транспортного средства" << vehicleId << std::endl;
}
