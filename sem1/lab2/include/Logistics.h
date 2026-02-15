#pragma once
#include <vector>
#include "IOrder.h"
#include "IVehicle.h"
#include "Manager.h"
#include "RouteOptimizer.h"
#include "RoutePlanner.h"
#include "ManagerCoordinator.h"

class IOrder;
class IVehicle;
class Manager;
class RouteOptimizer;
class RoutePlanner;
class ManagerCoordinator;

class Logistics
{
private:
    std::vector<IOrder *> orders;
    std::vector<IVehicle *> vehicles;
    std::vector<Manager *> managers;
    RouteOptimizer optimizer;
    RoutePlanner *routePlanner;
    ManagerCoordinator *managerCoordinator;

public:
    Logistics(std::vector<IOrder *> orders, std::vector<IVehicle *> vehicles, std::vector<Manager *> managers,
              RouteOptimizer optimizer, RoutePlanner *rp, ManagerCoordinator *mc);
    Logistics() {}
    std::vector<IOrder *> getOrders();
    void addOrder(IOrder *order);
    void addVehicle(IVehicle *vehicle);
    void addManager(Manager *manager);
    bool checkAvailability(IVehicle *vehicle);
    void planRoute(IOrder *order);
};