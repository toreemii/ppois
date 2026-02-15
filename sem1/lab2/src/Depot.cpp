#include "../include/Depot.h"

Depot::Depot(std::string depotId) : depotId(depotId) {}

std::vector<Vehicle *> Depot::getVehicles()
{
    return vehicles;
}

std::string Depot::getDepoId()
{
    return depotId;
}

void Depot::addVehicle(Vehicle *vehicle)
{
    vehicles.push_back(vehicle);
    vehicle->setStatus(1);
    std::cout << "Транспорт добавлен в депо" << depotId << std::endl;
}

void Depot::removeVehicle(Vehicle *vehicle)
{
    auto it = std::find(vehicles.begin(), vehicles.end(), vehicle);
    if (it != vehicles.end())
    {
        vehicles.erase(it);
        std::cout << "Транспорт удалён из депо " << depotId << std::endl;
    }
}

void Depot::loadFreight(Freight *freight, Vehicle *vehicle)
{
    if (std::find(vehicles.begin(), vehicles.end(), vehicle) != vehicles.end())
    {
        vehicle->loadCargo(freight->getWeight());
        std::cout << "Груз загружен в транспортное средство на складе" << depotId << std::endl;
    }
}

void Depot::scheduleMaintenance(Vehicle *vehicle, Maintenance *maintenance)
{
    maintenance->fixPart("Двигатель");
    vehicle->setStatus(-1);
    std::cout << "Планируется техническое обслуживание транспортного средства в депо" << depotId << std::endl;
}