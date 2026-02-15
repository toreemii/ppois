#include "../include/RoutePlanner.h"
#include <iostream>

void RoutePlanner::planRoute(IOrder *order)
{
    std::cout << "Маршрут спланирован для заказа: " << order->getOrderId() << std::endl;
}