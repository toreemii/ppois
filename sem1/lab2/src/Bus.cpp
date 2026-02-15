#include "../include/Bus.h"

Bus::Bus(Fuel *fuel, double maxSpeed, int capacityPeople, double capacityCargo, VehicleStatus status)
    : Vehicle(fuel, maxSpeed, capacityPeople, capacityCargo, status) {}

void Bus::loadCargo(double weight)
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

void Bus::loadPeople(int people)
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

void Bus::unloadCargo(double weignt)
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

void Bus::unloadPeople(int people)
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

double Bus::calculateFuelConsumption(double distance) const
{
    return (distance / 100) * 16;
}