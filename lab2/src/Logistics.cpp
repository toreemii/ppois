#include "../include/Logistics.h"
#include <iostream>

Logistics::Logistics(std::vector<IOrder *> orders, std::vector<IVehicle *> vehicles, std::vector<Manager *> managers, RouteOptimizer optimizer,
                     RoutePlanner *rp, ManagerCoordinator *mc)
    : orders(orders), vehicles(vehicles), managers(managers), optimizer(optimizer), routePlanner(rp), managerCoordinator(mc) {}

std::vector<IOrder *> Logistics::getOrders()
{
    return orders;
}

void Logistics::addOrder(IOrder *order)
{
    orders.push_back(order);
    std::cout << "Заказ" << order->getOrderId() << "добавлен в логистику\n";
}

void Logistics::addVehicle(IVehicle *vehicle)
{
    vehicles.push_back(vehicle);
    std::cout << "Транспорт добавлен в логистику\n";
}

void Logistics::addManager(Manager *manager)
{
    managerCoordinator->addManager(manager);
}

bool Logistics::checkAvailability(IVehicle *vehicle)
{
    return vehicle->getStatus() == "Available";
}

void Logistics::planRoute(IOrder *order)
{
    routePlanner->planRoute(order);
}