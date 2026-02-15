#pragma once
#include "IOrder.h"
#include "Depot.h"

class OrderAssigner {
public:
    void assignOrderToDepot(IOrder* order, Depot* depot, int maxOrderCapacity);
};