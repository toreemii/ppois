#include "../include/Car.h"

Car::Car(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status)
    : Vehicle(fuel, maxSpeed, capacityPeople, capacityCargo, status) {}

void Car::loadCargo(double weight)
{
    if (weight <= capacityCargo)
    {
        currentCargo = weight;
    }
    else
    {
        std::cout << "Вес превышает максимально допустимый.";
    }
}

void Car::loadPeople(int people)
{
    if (people <= capacityPeople)
    {
        currentPeople = people;
    }
    else
    {
        std::cout << "Количество людей превышает максимально допуситмое.";
        return;
    }
}

void Car::unloadCargo(double weignt)
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

void Car::unloadPeople(int people)
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

double Car::calculateFuelConsumption(double distance) const
{
    return (distance / 100) * 8;
}