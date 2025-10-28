#pragma once
#include <string>
#include <vector>
#include <ctime>
#include "Freight.h"
#include "Passenger.h"
#include "Vehicle.h"
#include "Order.h"
#include "GPS.h"
#include "Exceptions.h"

class Shipment
{
private:
    std::string shipmentId;
    Freight *cargo;
    std::vector<Passenger> passengers;
    Vehicle *assignedVehicle;
    Order *relatedOrder;
    double shipmentWeight;
    double shipmentVolume;
    double maxTemperature;
    double minTemperature;
    std::string handlingInstructions;
    int shipmentPriority;
    bool insuranceStatus;
    int deliveryAttempts;
    std::string trackingStatus;
    std::tm estimatedDeliveryTime;

public:
    Shipment(std::string shipmentId, Order *order);
    void startShipment();
    void trackShipment(GPS *gps);
    void completeShipment();
    std::string getShipmentId();
    Order *getRelatedOrder();
    void setVehicle(Vehicle *vehicle);
    void updateTrackingStatus(std::string status);
    bool checkTemperatureCompliance(double currentTemp) const;
    void incrementDeliveryAttempts();
    double calculateShipmentCost() const;
    void logShipmentStatus() const;
    void validateHandlingInstructions() const;
    void setShipmentWeight(double shipmentWeight);
    double getShipmentWeight();
    int getDeliveryAttempts();
};