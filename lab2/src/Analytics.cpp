#include "../include/Analytics.h"

Analytics::Analytics(double totalFuelConsumption, std::vector<IOrder *> analyzedOrders)
    : totalFuelConsumption(totalFuelConsumption), analyzedOrders(analyzedOrders) {}

double Analytics::getTotalFuelConsumption()
{
    return totalFuelConsumption;
}

void Analytics::addOrder(IOrder *order)
{
    this->analyzedOrders.push_back(order);
}

double Analytics::calculateFuelEfficiency(IVehicle *vehicle, double distance)
{
    double consumption = vehicle->calculateFuelConsumption(distance);
    totalFuelConsumption += consumption;
    return consumption / distance;
}

void Analytics::analyzedOrderCompletion(IOrder *order)
{
    std::cout << "Выполнение " << order->getOrderId() << "заказа проанализировано" << std::endl;
}

std::vector<std::string> Analytics::generateReport(std::vector<IOrder *> orders)
{
    std::vector<std::string> report;
    for (auto *order : orders)
    {
        report.push_back("Order ID: " + order->getOrderId());
    }
    return report;
}
