#pragma once
#include <string>
#include "OperationsMonitor.h"
#include "Vehicle.h"
#include "Shipment.h"
class DispatchCenter
{
private:
    std::string centerId;
    std::vector<Vehicle *> vehicles;
    std::vector<Shipment *> shipments;
    OperationsMonitor *monitor;

public:
    DispatchCenter(std::string centerId, OperationsMonitor *monitor, std::vector<Vehicle *> vehicles, std::vector<Shipment *> shipments);
    void assignVehicleToShipment(Vehicle *vehicle, Shipment *shipment);
    void monitorOperations();
    std::string getCenterId();
};