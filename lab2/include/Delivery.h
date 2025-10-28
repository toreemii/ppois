#pragma once
#include <string>
#include "Shipment.h"
#include "Notification.h"

class Delivery
{
private:
    std::string deliveryId;
    Shipment *shipment;

public:
    Delivery(std::string deliveryId, Shipment *shipment);
    void initiateDelivery();
    void confirmDelivery(Notification *notification);
    std::string getDeliveryId();
};