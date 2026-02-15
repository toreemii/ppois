#include "../include/Train.h"

Train::Train(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status)
    : Vehicle(fuel, maxSpeed, capacityPeople, capacityCargo, status) {}

void Train::loadCargo(double weight)
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

double Train::getCurrentCargo()
{
    return currentCargo;
}

int Train::getCurrentPeople()
{
    return currentPeople;
}

void Train::loadPeople(int people)
{
    if (people <= capacityPeople)
    {
        currentPeople = people;
    }
    else
    {
        throw PassengerLimitException();
    }
}

void Train::unloadCargo(double weight)
{
    if (weight >= currentCargo)
    {
        std::cout << "Ошибка: невозможно выгрузить больше груза, чем есть.";
        return;
    }
    else
    {
        currentCargo -= weight;
    }
}

void Train::unloadPeople(int people)
{
    if (people >= currentPeople)
    {
        std::cout << "Ошибка: невозможно выгрузить больше людей, чем есть.";
        return;
    }
    else
    {
        currentPeople -= people;
    }
}

double Train::calculateFuelConsumption(double distance) const
{
    return (distance / 100) * 600;
}

double Train::estimateTravelTime(double distance) const
{
    return distance / maxSpeed;
}

void Train::updateOdometer(double distance)
{
    odometerReading += distance;
}

bool Train::checkMaintenanceDue() const
{
    time_t now = time(0);
    std::tm current = *localtime(&now);
    return difftime(mktime(&current), mktime(const_cast<std::tm *>(&lastMaintenanceDate))) > 31536000;
}

double Train::calculateTotalCost(double distance) const
{
    return calculateFuelConsumption(distance) * 1.2;
}

void Train::logTripStart() const
{
    std::cout << "Началaсь поездка на поезде для транспортного средства " << vehicleId << std::endl;
}

void Train::logTripEnd() const
{
    std::cout << "Поездка на поезде завершена для транспортного средства" << vehicleId << std::endl;
}

bool Train::verifyInsurance() const
{
    return isInsured;
}

void Train::adjustTirePressure(double pressure)
{
    tirePressure = pressure;
}

std::string Train::getVehicleDetails() const
{
    return "Поезд: модель " + model + ", год " + std::to_string(manufactureYear);
}

void Train::performSelfCheck() const
{
    std::cout << "Проверка поезда: топливо " << currentFuelLevel << ", одометр " << odometerReading << std::endl;
}