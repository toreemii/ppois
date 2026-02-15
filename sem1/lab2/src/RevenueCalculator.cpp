#include "../include/RevenueCalculator.h"

void RevenueCalculator::computeRevenue(TransportCompany *company)
{
    double total = 0.0;
    for (const auto &order : company->getOrders())
    { 
        total += order->getTotalCost();
    }
   
}