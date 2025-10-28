#include "../include/OperationsMonitor.h"

OperationsMonitor::OperationsMonitor(std::vector<IVehicle*> monitoredVehicles, std::vector<Shipment> monitoredShipments, GPS *trackingSystem)
    : monitoredVehicles(monitoredVehicles), monitoredShipments(monitoredShipments), trackingSystem(trackingSystem) {}

void OperationsMonitor::monitorVehicle(IVehicle* vehicle)
{
    monitoredVehicles.push_back(vehicle);
    auto [x, y] = vehicle->getLocation();
    std::cout << "Мониторинг автомобиля на " << x << " " << y << std::endl;
}

void OperationsMonitor::alertDelay(Shipment *shipment)
{
    std::cout << "Оповещение о задержке отправки" << shipment->getShipmentId() << std::endl;
}
std::vector<IVehicle*> OperationsMonitor::getMonitoredVehicles()
{
    return monitoredVehicles;
}
