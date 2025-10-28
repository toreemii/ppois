#include "../include/DispatchCenter.h"

DispatchCenter::DispatchCenter(std::string centerId, OperationsMonitor *monitor, std::vector<Vehicle *> vehicles, std::vector<Shipment *> shipments)
    : centerId(centerId), monitor(monitor), vehicles(vehicles), shipments(shipments) {}

std::string DispatchCenter::getCenterId()
{
    return centerId;
}
void DispatchCenter::assignVehicleToShipment(Vehicle *vehicle, Shipment *shipment)
{
    if (vehicle && shipment)
    {
        vehicles.push_back(vehicle);
        shipments.push_back(shipment);
        shipment->setVehicle(vehicle);
        std::cout << "Транспорт назначен для отправки " << shipment->getShipmentId()
                  << " из центра " << centerId << std::endl;
    }
    else
    {
        throw std::runtime_error("Транспорт или отправка не указаны");
    }
}

void DispatchCenter::monitorOperations()
{
    if (monitor)
    {
        for (const auto &vehicle : vehicles)
        {
            monitor->monitorVehicle(vehicle);
        }
        std::cout << "Операции мониторятся в центре " << centerId << std::endl;
    }
}
