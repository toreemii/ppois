#pragma once
#include "Order.h"
#include <vector>
#include <string>
#include "Logistics.h"
#include "IOrder.h"

class Analytics
{
private:
    double totalFuelConsumption;
    std::vector<IOrder*> analyzedOrders;

public:
    Analytics(double totalFuelConsumption, std::vector<IOrder*> analyzedOrders);
    Analytics() {};
    std::vector<std::string> generateReport(std::vector<IOrder *> orders);
    void analyzedOrderCompletion(IOrder *order);
    double getTotalFuelConsumption();
    void addOrder(IOrder *order);
    double calculateFuelEfficiency(IVehicle* vehicle, double distance);
};