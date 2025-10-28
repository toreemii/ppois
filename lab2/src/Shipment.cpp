#include "../include/Shipment.h"

Shipment::Shipment(std::string shipmentId, Order *order) : shipmentId(shipmentId), relatedOrder(order), cargo(nullptr) {}

std::string Shipment::getShipmentId()
{
    return shipmentId;
}

void Shipment::setShipmentWeight(double shipmentWeight)
{
    this->shipmentWeight = shipmentWeight;
}

double Shipment::getShipmentWeight()
{
    return shipmentWeight;
}

int Shipment::getDeliveryAttempts()
{
    return deliveryAttempts;
}

void Shipment::startShipment()
{
    assignedVehicle->setStatus(0);
    std::cout << "Отправка " << shipmentId << " началась" << std::endl;
}
void Shipment::trackShipment(GPS *gps)
{
    auto [lat, lon] = assignedVehicle->getLocation();
    std::cout << "Груз " << shipmentId << " в (" << lat << ", " << lon << ")" << std::endl;
}
void Shipment::completeShipment()
{
    assignedVehicle->setStatus(1);
    std::cout << "Отгрузка " << shipmentId << " завершена" << std::endl;
}
Order *Shipment::getRelatedOrder()
{
    return relatedOrder;
}

void Shipment::setVehicle(Vehicle *vehicle)
{
    this->assignedVehicle = vehicle;
}
void Shipment::updateTrackingStatus(std::string status)
{
    trackingStatus = status;
}

bool Shipment::checkTemperatureCompliance(double currentTemp) const
{
    return currentTemp >= minTemperature && currentTemp <= maxTemperature;
}

void Shipment::incrementDeliveryAttempts()
{
    deliveryAttempts++;
}

double Shipment::calculateShipmentCost() const
{
    return shipmentWeight * 0.1 + shipmentVolume * 0.05;
}

void Shipment::logShipmentStatus() const
{
    std::cout << "Отгрузка " << shipmentId << ": Статус " << trackingStatus << std::endl;
}

void Shipment::validateHandlingInstructions() const
{
    if (handlingInstructions.empty())
    {
        throw ShipmentErrorException();
    }
}