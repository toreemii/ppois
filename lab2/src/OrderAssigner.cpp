#include "../include/OrderAssigner.h"
#include "../include/Exceptions.h"

void OrderAssigner::assignOrderToDepot(IOrder *order, Depot *depot, int maxOrderCapacity)
{
    if (maxOrderCapacity <= 0)
    { 
        throw RoutePlanningException();
    }
    depot->addVehicle(order->getVehicle());
}