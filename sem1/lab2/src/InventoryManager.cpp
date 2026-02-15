#include "../include/InventoryManager.h"

InventoryManager::InventoryManager(std::string managerId, std::vector<Warehouse *> warehouses)
    : managerId(managerId), warehouses(warehouses) {}

std::string InventoryManager::getManagerId()
{
    return managerId;
}
void InventoryManager::addWarehouse(Warehouse *warehouse)
{
    warehouses.push_back(warehouse);
    std::cout << "Склад " << warehouse->getWarehouseId() << " добавлен в управление: " << managerId << std::endl;
}

void InventoryManager::manageInventory(Freight *freight, Warehouse *warehouse)
{
    if (warehouse->checkCapacity())
    {
        warehouse->storeFreight(freight);
        std::cout << "Груз " << freight->getFreightId() << " управляется: " << managerId << std::endl;
    }
    else
    {
        throw std::runtime_error("Недостаточно места на складе");
    }
}
