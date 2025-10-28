#pragma once
#include "Vehicle.h"
#include "Shipment.h"
#include "GPS.h"
#include <vector>
class OperationsMonitor
{
private:
    std::vector<IVehicle*> monitoredVehicles;
    std::vector<Shipment> monitoredShipments;
    GPS *trackingSystem;

public:
    OperationsMonitor(std::vector<IVehicle*> monitoredVehicles, std::vector<Shipment> monitoredShipments, GPS *trackingSystem);
    void monitorVehicle(IVehicle *vehicle);
    void alertDelay(Shipment *shipment);
    std::vector<IVehicle*> getMonitoredVehicles();
};