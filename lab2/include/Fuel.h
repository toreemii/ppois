#pragma once
#include <string>
#include "Exceptions.h"

class Fuel
{
protected:
    std::string fuelType;
    double availableAmount;
    double costPerUnit;
    double amount;

public:
    Fuel(std::string type, double amount, double cost);
    virtual double calculateCost(double amount) const;
    void refuel(double amount);
    double getCostPerUnit() const;
    double getAvailableAmount() const;
    std::string getFuelType() const;
    void addAmount(double amount);
    virtual std::string getUnit() const { return "liters"; }
};

class Electric : public Fuel
{
public:
    Electric(double amount, double cost);
    double calculateCost(double amount) const override;
    std::string getUnit() const override;
};

class Diesel : public Fuel
{
public:
    Diesel(double amount, double cost);
    double calculateCost(double amount) const override;
    std::string getUnit() const override;
};

class Gasoline : public Fuel
{
public:
    Gasoline(double amount, double cost);
    double calculateCost(double amount) const override;
    std::string getUnit() const override;
};
