#include "../include/Ship.h"

Ship::Ship(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status)
    : Vehicle(fuel, maxSpeed, capacityPeople, capacityCargo, status) {}

void Ship::loadCargo(double weight)
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

double Ship::getTirePressure()
{
    return tirePressure;
}

double Ship::getOdometerReading()
{
    return odometerReading;
}

double Ship::getCurrentCargo()
{
    return currentCargo;
}

int Ship::getCurrentPeople()
{
    return currentPeople;
}

void Ship::loadPeople(int people)
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

void Ship::unloadCargo(double weignt)
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

void Ship::unloadPeople(int people)
{
    if (people >= currentPeople)
    {
        std::cout << "Ошибка:невозможно выгрузить больше людей, чем есть.";
        return;
    }
    else
    {
        currentPeople -= people;
    }
}

double Ship::calculateFuelConsumption(double distance) const
{
    return (distance / 100) * 409500;
}

double Ship::estimateTravelTime(double distance) const
{
    return distance / maxSpeed;
}

void Ship::updateOdometer(double distance)
{
    odometerReading += distance;
}

bool Ship::checkMaintenanceDue() const
{
    time_t now = time(0);
    std::tm current = *localtime(&now);
    return difftime(mktime(&current), mktime(const_cast<std::tm *>(&lastMaintenanceDate))) > 31536000;
}

double Ship::calculateTotalCost(double distance) const
{
    return calculateFuelConsumption(distance) * 1.5;
}

void Ship::logTripStart() const
{
    std::cout << "Началaсь поездка на корабле для транспортного средства " << vehicleId << std::endl;
}

void Ship::logTripEnd() const
{
    std::cout << "Поездка на корабле завершена для транспортного средства" << vehicleId << std::endl;
}

bool Ship::verifyInsurance() const
{
    return isInsured;
}

void Ship::adjustTirePressure(double pressure)
{
    tirePressure = pressure;
}

std::string Ship::getVehicleDetails() const
{
    return "Корабль: ID " + vehicleId + ", грузоподъемность " + std::to_string(capacityCargo) + ", мест " + std::to_string(capacityPeople);
}

void Ship::performSelfCheck() const
{
    std::cout << "Проверка корабля: топливо " << fuel->getAvailableAmount()
              << ", одометр " << odometerReading << std::endl;
}