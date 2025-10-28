#include "../include/Delivery.h"

Delivery::Delivery(std::string deliveryId, Shipment *shipment) : deliveryId(deliveryId), shipment(shipment) {}

std::string Delivery::getDeliveryId()
{
    return deliveryId;
}

void Delivery::initiateDelivery()
{
    shipment->startShipment();
    std::cout << "Доставка " << deliveryId << " начата" << std::endl;
}

void Delivery::confirmDelivery(Notification *notification)
{
    shipment->completeShipment();                                
    notification->notifyOrderStatus(shipment->getRelatedOrder()); 
    std::cout << "Доставка " << deliveryId << " подтверждена" << std::endl;
}
