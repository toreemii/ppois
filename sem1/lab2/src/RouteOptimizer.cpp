#include "../include/RouteOptimizer.h"
#include <iostream>

void RouteOptimizer::optimizeRoute(Order *order)
{
    std::cout << "Маршрут оптимизирован для заказа: " << order->getOrderId() << std::endl;
}