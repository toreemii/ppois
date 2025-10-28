#include "../include/Fuel.h"

Fuel::Fuel(std::string type, double amount, double cost)
    : fuelType(type), availableAmount(amount), costPerUnit(cost) {}

double Fuel::calculateCost(double amount) const
{
    return amount * costPerUnit;
}

void Fuel::refuel(double amount)
{
    availableAmount += amount;
    if (amount <= 0)
    {
        throw FuelErrorException();
    }
}

void Fuel::addAmount(double amount)
{
    this->amount += amount;
}
double Fuel::getCostPerUnit() const
{
    return costPerUnit;
}

double Fuel::getAvailableAmount() const
{
    return availableAmount;
}

std::string Fuel::getFuelType() const
{
    return fuelType;
}

Electric::Electric(double amount, double cost)
    : Fuel("Electric", amount, cost) {}

double Electric::calculateCost(double amount) const
{
    return amount * costPerUnit;
}

std::string Electric::getUnit() const
{
    return "кВт*ч";
}

Diesel::Diesel(double amount, double cost)
    : Fuel("Diesel", amount, cost) {}

double Diesel::calculateCost(double amount) const
{
    return amount * costPerUnit;
}

std::string Diesel::getUnit() const
{
    return "liters";
}

Gasoline::Gasoline(double amount, double cost)
    : Fuel("Gasoline", amount, cost) {}

double Gasoline::calculateCost(double amount) const
{
    return amount * costPerUnit;
}

std::string Gasoline::getUnit() const
{
    return "liters";
}
